#pragma once

#include <utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <ATMega162_driver.h>
#include <SRAM_driver.h>
#include <ADC_driver.h>
#include <SPI_driver.h>
#include "oled_driver.h"
#include "menu.h"
#include "CAN_driver.h"
#include "mcp2515_driver.h"


typedef struct{
    uint8_t X;
    uint8_t Y;
}Touch;


void send_joystick(Joystick *jstk);
void send_buttons(Buttons *btns);
void send_touch(Touch *t);

void io_send();

typedef struct{

    uint8_t RXB0SIDH;
    uint8_t RXB0SIDL;
    uint8_t RXB0EID8;
    uint8_t RXB0EID0;
    uint8_t RXB0DLC;
    union {
        uint8_t byte[8];
        Byte8   byte8;
    };
    uint8_t CANSTAT;

}CAN_msg1;



typedef struct CanMsg CanMsg;
struct CanMsg {
    uint8_t id;
    uint8_t length;
    union {
        uint8_t     byte[8];
        uint32_t    dword[2];
        Byte8       byte8;
    };    
};