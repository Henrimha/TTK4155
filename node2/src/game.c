#include "game.h"


void joystick_drive(){

    // les joystick fra can
    CanMsg m;
    int a = 0;
    Joystick j;

    a = can_rx(&m);
    if (a){printf("can_rx, baby\n\r");}
    if(m.length=3){
        
        printf("lengde 3\n\r");
    } 

    j.X = m.byte[0];
    j.Y = m.byte[1];
    j.btn = m.byte[2];

    printf ("x=%d\n\r",j.X);
    printf ("y=%d\n\r",j.Y);
    printf ("btn=%d\n\n\r",j.btn);
    // putt joystick x/y inn i pwm_set()
    
}

// typedef struct CanMsg CanMsg;
// struct CanMsg {
//     uint8_t id;
//     uint8_t length;
//     union {
//         uint8_t     byte[8];
//         uint32_t    dword[2];
//         Byte8       byte8;
//     };    
// };
