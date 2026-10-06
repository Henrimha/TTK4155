#include "CAN_driver.h"

#define RESET ((1<<7)|(1<<6))
#define READ ((1<<1)|(1<<0))
#define READ_RX_BUFFER (())
#define WRITE((1<<1))
#define READ_STATUS((1<<7)|(1<<5))
#define RX_STATUS((0b1011 0000))
#define BIT_MODIFY((0b0000 0101))
void CAN_init(){
    //Need to delay 128 clock cycles

    //For now set after configuration state, loopback mode: when connecting others use normal mode
    //Reset command
    //wait 128 clock cycles


}