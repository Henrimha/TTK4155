#include "game.h"



void send_joystick(){
    Joystick joystick = joystick_read_scale();
    char message[] = {joystick.X, joystick.Y, joystick.btn};
    CAN_send(3, message);
}