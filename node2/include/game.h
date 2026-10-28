#include <stdio.h>
#include <stdarg.h>
#include "can.h"
#include "sam.h"
#include "uart.h"
#include "PWM_driver.h"





typedef struct{
    uint8_t X; 
    uint8_t Y;
    uint8_t btn;
}Joystick;


void joystick_drive();