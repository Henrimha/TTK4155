#include <oled_driver.h>

//#define FD (~(1<<1))
//#define AE ((1<<7)|(1<<5)|(1<<3)|(1<<2)|(1<<1)|(1<<0))
//#define A12 ((1<<4)|(0<<2)|(1<<1))
#define A70 (1<<7)
#define A6h ((1<<7)|(1<<5)|(1<<2)|(1<<1)|(0<<0))

void oled_init(void){
    oled_command(0xFD); //MCU protection status
    oled_command(0x12); //unlock
    //set contrast
    oled_command(0x81); //Set control
    oled_command(A70); //Control
    
    oled_command(A6h); //Normal display, not inverse

    //When using internal clock? use command D5h A[7:4] to change frequency
    //DCLK = Fosc/D, reduces frame rate?
    //Frm can be reduced by D5h A[3:0]
    //Set Display OFF/ON AEh/AFh
    oled_command(0xAF); //display on

    

    return;
}
//Frame frequency of display

void oled_shutdown(void){
    oled_command(0xAE);//display off
    oled_command(0xFD); //MCU protection status
    oled_command(0x16); //lock
}