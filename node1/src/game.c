#include "game.h"



void send_joystick(){
    Joystick joystick = joystick_read_scale();
    char message[] = {joystick.X, joystick.Y, joystick.btn};
    // oled_print("hei:) ");
    char X[5];
    itoa(joystick.X, X, 10);
    // oled_clear();
    oled_goto_page_column(0,0);
    oled_print(X);
    oled_print(" ");

    char y[5];
    itoa(joystick.Y, y, 10);
    // oled_clear();
    oled_goto_page_column(1,0);
    oled_print(y);
    oled_print(" ");
    CAN_send(3, message);
}