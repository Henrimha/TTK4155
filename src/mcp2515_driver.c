#include "mcp2515_driver.h"

void mcp2515_init(){
    mcp2515_transmit(RESET);
    // delay 128 cock cycles
    for (char i = 0; i < 16; i++) {
        SPDR = 0x00;
        while (!(SPSR & (1 << SPIF)));
    }
    
    
    mcp2515_bit_modify(MCP_CANCTRL, , MODE_LOOPBACK)
    mcp2515_write
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