#include "game.h"


void joystick_control(CanMsg *m){

    int a = 0;
    Joystick j;
    if (m->length != 3) {
        printf("Wrong CAN message length: %d\n\r", m->length);
        return;
    }
    j.X = m->byte[0];
    j.Y = m->byte[1];
    j.btn = m->byte[2] ;
    PWM_set(j.X);

    //printf("Y = %d     ", j.Y);
    // calculate_thrust(j.Y);

    
}



void buttons_control(CanMsg *m){
    Buttons b;
    
    b.right = m->byte[0];
    b.left = m->byte[1];
    b.nav = m->byte[2];

    bool sr1 = (b.left & (1 << 7)) != 0;
    // sr2 funker ikke
    // sr3 funker ikke
    bool sr4 = (b.right & (1 << 2)) != 0;
    bool sr5 = (b.right & (1 << 3)) != 0;
    bool sr6 = (b.right & (1 << 4)) != 0;

    //sl1 funker ikke
    bool sl2 = (b.left & (1 << 0)) != 0;
    bool sl3 = (b.left & (1 << 2)) != 0;
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
        solenoid_shoot();
    }



    b.left = m->byte[1];
    b.nav = m->byte[2];

}


void touch_control(CanMsg *m){
    Touch t = {m->byte[0], m->byte[1]};
    REF=t.X;
    calculate_thrust();
}

// void IR_send(){
//     int IR = ADC_sample();
//     CanMsg c;
//     c.id = IR; //Lag Enum som sier hva IR er, tilsvarende som button og joystick
//     c.length = 8;

//     // Send Bestemt meding som betyr IR brutt
    
//     can_tx();


// }
