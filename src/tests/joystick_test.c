#include "tests/joystick_test.h"

void joystick_test (void){

    while(1){

        Joystick joystick = joystick_read();
        // printf("%d\n\r", joystick.X);
        // printf("%d\n\r", joystick.Y);
        printf("%d\n\r", joystick.btn);

        _delay_ms(200);

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