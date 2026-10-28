#include "game.h"


void joystick_control(){

    // les joystick fra can
    CanMsg m;
    int a = 0;
    Joystick j;

    a = can_rx(&m);
    printf(" a:  %d\n\r", a);
    if (a){printf("can_rx, baby\n\r");}
    // if(m.length=3){
        
    //     printf("lengde 3\n\r");
    // } 

    j.X = m.byte[0];
    j.Y = m.byte[1];
    j.btn = m.byte[2] ;

    printf("x = %d, y = %d, btn = %d\n\r", j.X, j.Y, j.btn);


    PWM_set(j.X);

    // dcmotor_set(j.Y); // TODO: lag denne
    
}



void buttons_control(){
    CanMsg m;
    int a = 0;
    Buttons b;
    a = can_rx(&m);
    
    b.right = m.byte[0];

    char sr5 = (b.right & (1 << 3)); // sr5 vil være 8, men behandle det som bools videre
    if(sr5){
        // kjør solenoide ... 
    }

    b.left = m.byte[1];
    b.nav = m.byte[2];

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
