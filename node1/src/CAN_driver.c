#include "CAN_driver.h"
#include "MCP2515.h"
#include "mcp2515_driver.h"

// #define MCP_RESET ((1<<7)|(1<<6))
#define READ ((1<<1) | (1<<0))
#define MCP_READ_RX_BUFFER (0b10010000)
#define MCP_LOAD_TX_BUFFER ( 0b01000000) //Buffer 0 ink identefier
#define WRITE (1<<1)
#define READ_STATUS ((1<<7) | (1<<5))
// #define RX_STATUS (0b10110000)
#define BIT_MODIFY (0b00000101)
#define CANCTRL (0b00001111)
#define DUMMY_ADRESS (0b00000000)
#define MCP_TXRTSCRTL (0x0D)
void CAN_init(){
    //Need to delay 128 clock cycles 

    //The clock is 84MHz, each bit is , this is the half the limit of the MCP2551 and the SAM3X which has a limit of 1Mb/s

    //new CAN init
    mcp2515_bit_modify(MCP_TXRTSCRTL, 0b00000111, 0x00); // Disable requesting message transmission of the T buffers on the pins, they are input pins
    mcp2515_bit_modify(MCP_RXB0CTRL, 0b01100100, 0b01100000); // No filters, recieve all messages. Will get data up to an error, No remote transfer request recieved, no rollover,
    mcp2515_bit_modify(MCP_TX01_INT, 0b00001100, 0x00); // RX0BF and RX1BF are set to high impedance, unused
    mcp2515_bit_modify(MCP_CNF1, 0xff, 0b00000011); //SJW=1, short distance and good oscilators. BRP=3 meaning, so TQ=500ns
    mcp2515_bit_modify(MCP_CNF2, 0xff, (1<<7)|(0<<6)|(0b110<<3)|(0b01<<0)); // BTLMODE=1, sample once, PS1=6+1=7, Phase seg for distance=2
    mcp2515_bit_modify(MCP_CNF3, 0b00000111, 0x05); //PS2=5+1=6
    //SyncSeg + PropSeg+PS1+PS2=16, sample at 10/16=62.5%
    mcp2515_bit_modify(MCP_CANINTE, 0xFF,0b000000001); //enable interrupt



    // mcp2515_bit_modify(MCP_CANCTRL, 0b11100011, MODE_LOOPBACK); // sLoopbak mode set
    mcp2515_bit_modify(MCP_CANCTRL, 0b11100011, MODE_NORMAL); // sNormal mode set
    mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00);


}

void CAN_read(CanMsg* rData){
    char data[14] = {MCP_READ_RX_BUFFER,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    SPI_array_transmit(data,CAN_CONTROLLER,14,data);

    
    uint8_t id1 = (data[1] >> 5); // RXB0SIDL
    uint8_t id2 = (data[0] << 3); // RXB0SIDH
    uint8_t id = id1|id2;
    rData->id = id;

    rData->length = data[4] & (0x0f); // RXB0DLC bits 0-4

    for (int i = 0; i < 8; i++){
        rData->byte[i] = data[i+5];
    }

    
    return;
}



#define MCP_TXB0SIDH 0x31
#define MCP_TXB0SIDL 0x32

//identefier 0x123 0000 0001 0010 0011, 11 bit, 1 mask 0000000001 filter bit1 = 1 0x123 
//Automatisk laveste priority
void CAN_send_extended(uint16_t identifier, char length, char RTR, char *sData){
    if(mcp2515_read(MCP_TXB0CTRL) & (1<<3)){
        return;
    }

    char data[14];
    data[0] = MCP_LOAD_TX_BUFFER; 
    data[1] = (identifier >> 3) & 0xFF; 
    data[2] = (identifier & 0x07) <<5; 
    // data[2] &= ~(1<<3);
    data[3] = 0b00000000;
    data[4] = 0b00000000;
    data[5] = length & 0x0F;
    if (RTR){data[5] |= 1<<6;} 
    
  
    for (int i = 0; i < length; i++){
        data[6+i] = sData[i];
    }

    SPI_array_send (data, CAN_CONTROLLER, (6+length));
    char rts = 0x81;
    SPI_array_send(&rts, CAN_CONTROLLER, 1);
    // mcp2515_bit_modify(MCP_TXB0CTRL, (1<<3), (1<<3)); //Buffer is currently pending transmission
  

}

