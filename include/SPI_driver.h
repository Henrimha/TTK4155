#pragma once
#include "utils.h"

typedef enum{
    IO_BOARD,
    OLED_SCREEN,
    CAN_CONTROLLER
} Slaves;

void SPI_Init(void);

char SPI_shout(char cData);

char IO_transmit(char data);

char oled_transmit(char data, int command);

char SPI_transmit(char cData, Slaves slave);





typedef struct __attribute__((packed)) {
    union {
        uint8_t right;
        struct {
            uint8_t R1:1;
            uint8_t R2:1;
            uint8_t R3:1;
            uint8_t R4:1;
            uint8_t R5:1;
            uint8_t R6:1;
        };
    };
    union {
        uint8_t left;
        struct {
            uint8_t L1:1;
            uint8_t L2:1;
            uint8_t L3:1;
            uint8_t L4:1;
            uint8_t L5:1;
            uint8_t L6:1;
            uint8_t L7:1;
        };
    };
    union {
        uint8_t nav;
        struct {
            uint8_t NB:1;
            uint8_t NR:1;
            uint8_t ND:1;
            uint8_t NL:1;
            uint8_t NU:1;
        };
    };
} Buttons;

Buttons Buttons_read(void);
void LED_enable(int LED_N, uint8_t state);
void LED_PWM(int LED_N, uint8_t width);

typedef struct{
    uint8_t X; 
    uint8_t Y;
    uint8_t btn;
}Joystick;

Joystick joystick_read (void);