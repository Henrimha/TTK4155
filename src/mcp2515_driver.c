#include "mcp2515_driver.h"
#define MCP_TXRTSCTRL (0b00001101)
#define MCP_BFPCTRL (0x0C)


void mcp2515_init(){
    mcp2515_transmit(RESET);
    // delay 128 cock cycles
    for (char i = 0; i < 16; i++) {
        SPDR = 0x00;
        while (!(SPSR & (1 << SPIF)));
    }

    mcp2515_bit_modify(MCP_TXRTSCTRL, 0b00000111, 0b01000000); //Disable requesting message transmission of the T buffers on the pins, they are input pins
    mcp2515_bit_modify(MCP_BFPCTRL, 0b0000 1100,0x00); //RX0BF and RX1BF are set to high impedance, unused
    
    
    mcp2515_bit_modify(MCP_CANCTRL, 0b11100011, MODE_LOOPBACK); // sets F_clkout to System clock/1
    
}

char mcp2515_read(char adress){
    char result[3];
    // PORTB &= ~(1 << CAN_CS);
    char sData[3] = {MCP_READ, adress, 0x00};
    SPI_array_transmit(sData, CAN_CONTROLLER, 3, result);
    return result[2];
}

void mcp2515_write(char adress, char data){
    char sData[3] = {MCP_WRITE, adress, data}; 
    SPI_array_send(sData, CAN_CONTROLLER, 3);
}

char mcp2515_read_status(){
    char result[3];
    char sData[3] = {MCP_READ_STATUS, 0x00, 0x00};
    SPI_array_transmit(sData, CAN_CONTROLLER, 3, result);
    return result[1];
}

void mcp2515_bit_modify(char adress, char mask, char data){
    char sData[4] = {MCP_BITMOD, adress, mask, data};
    SPI_array_send(sData, CAN_CONTROLLER, 4);
}

// 01000x