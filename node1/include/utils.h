#pragma once
#define F_CPU 4915200UL
#include <avr/io.h>
#include <util/delay.h>
#include "fonts.h"
#include "string.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/sleep.h>
#include <stdint.h>

typedef struct Byte8 Byte8;
struct Byte8 {
    uint8_t bytes[8];
};


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

extern volatile char INT1_FLAG;

extern volatile CanMsg CAN_RX_DATA;

extern volatile char TC3_FLAG;

extern volatile char GAMESTATE;

