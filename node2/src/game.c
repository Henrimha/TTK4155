#include "game.h"


void joystick_control(CanMsg *m){

    // les joystick fra can
    int a = 0;
    Joystick j;


    if (m->length != 3) {
        printf("Wrong CAN message length: %d\n\r", m->length);
        return;
    }

    // if (a){printf("can_rx, baby\n\r");}
    // else {printf("ikke baby, can_rx:(\n\r");}


    j.X = m->byte[0];
    j.Y = m->byte[1];
    j.btn = m->byte[2] ;

    // printf("x = %d, y = %d, btn = %d\n\r", j.X, j.Y, j.btn);


    PWM_set(j.X);

    // dcmotor_set(j.Y); // TODO: lag denne
    
}



void buttons_control(CanMsg *m){
    Buttons b;
    
    b.right = m->byte[0];
    b.left = m->byte[1];
    b.nav = m->byte[2];

    bool sr1 = (b.left & (1 << 7)) != 0;
    bool sr4 = (b.right & (1 << 2)) != 0;
    bool sr5 = (b.right & (1 << 3)) != 0;
    bool sr6 = (b.right & (1 << 4)) != 0;

    bool sl4 = (b.left & (1 << 2)) != 0;
    bool sl5 = (b.left & (1 << 3)) != 0;
    bool sl6 = (b.left & (1 << 4)) != 0;
    bool sl7 = (b.left & (1 << 5)) != 0;

    bool nu = (b.nav & (1 << 3)) != 0;
    bool nr = (b.nav & (1 << 0)) != 0;
    bool nd = (b.nav & (1 << 1)) != 0;
    bool nl = (b.nav & (1 << 2)) != 0;


    
    
    if(sr1){
        // kjør solenoide ...
        printf("sr5 baby\n\r"); 
    }

    b.left = m->byte[1];
    b.nav = m->byte[2];

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
