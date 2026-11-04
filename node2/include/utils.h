#pragma once
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

extern volatile char CAN_FLAG;

extern volatile CanMsg CAN_RX_DATA;

extern volatile char CT0_FLAG;

extern int PREVIOUS_VALUE;

extern int INTEGRATOR_STATE;
