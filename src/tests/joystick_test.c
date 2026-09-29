#include "tests/joystick_test.h"

void joystick_test (void){

    while(1){

        Joystick joystick = joystick_read();
        // printf("%d", joystick.X);
        // printf("%d", joystick.Y);
        printf("%d", joystick.btn);

        // _delay_ms(100);

    }
}

void buttons_test(void){
    while(1){
        Buttons buttons = Buttons_read();
        printf("%d ", buttons.left);
        printf("%d ", buttons.right);
        printf("%d\n\r", buttons.nav);
        _delay_ms(100);
    }
}