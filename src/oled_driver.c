#include <oled_driver.h>

//#define FD (~(1<<1))
//#define AE ((1<<7)|(1<<5)|(1<<3)|(1<<2)|(1<<1)|(1<<0))
//#define A12 ((1<<4)|(0<<2)|(1<<1))
#define A70 (1<<7)
#define A6h ((1<<7)|(1<<5)|(1<<2)|(1<<1)|(0<<0))
#define A4h ((1<<7)|(1<<5)|(1<<2)|(0<<0)) 
#define A0h ((1<<7)|(1<<5)|(0<<0))
#define C0h ((1<<7)|(1<<6)|(0<<3))

void oled_init(void){
    oled_command(0xFD); //MCU protection status
    oled_command(0x12); //unlock

    oled_command(0x2E);//no scrolling, (RAM data needs to be rewritten)
    oled_command(0x40); // set display start line is 0. RAM of 0 is 0
    //set contrast
    oled_command(0x81); //Set control
    oled_command(A70); //Control

    oled_command(A6h); //Normal display, not inverse
    oled_command(A4h); //Output follows RAM content (oled RAM)

    //We use internal clock, and do not care about update frequency.
    //to look at, Display clock, pre-charge period, VCOMH level, COM hardware configuration

    oled_command(0x20); //Set memory adressing mode
    oled_command(0x0); //Horizontal adressing mode

    oled_command(A0h); //set segment remap to 0, column 0 is to the left
    oled_command(C0h); //Scan direction is from COM0 to COM[N-1]

    oled_home(); //go to (0,0), can write everywhere
    
    oled_command(0xAF); //display on

    return;
}
//Frame frequency of display

void oled_shutdown(void){
    oled_command(0xAE);//display off
    oled_command(0xFD); //MCU protection status
    oled_command(0x16); //lock
    return;
}

void oled_home(){
    oled_command(0x21); //Setting column adress
    oled_command(0x0); //Start at 0
    oled_command(127); //end at 127

    oled_command(0x22); //set page adress
    oled_command(0); //start 0
    oled_command(7); //end 7
    return;
}