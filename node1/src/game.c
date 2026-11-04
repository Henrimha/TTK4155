#include "game.h"




void send_joystick(Joystick *jstk){
    
    char message[] = {jstk->X, jstk->Y, jstk->btn};


    char X[5];
    itoa(jstk->X, X, 10);
    oled_goto_page_column(0,0);
    oled_print(X);
    oled_print("  ");
    char y[5];
    itoa(jstk->Y, y, 10);
    oled_goto_page_column(1,0);
    oled_print(y);
    oled_print("  ");


    CAN_send_extended(JOYSTICK, 3, 0, message);
}


void send_buttons(Buttons *btns){
    char message[] = {btns->right, btns->left, btns->nav};

    char X[5];
    itoa(btns->right, X, 10);
    oled_goto_page_column(2,0);
    oled_print(X);
    oled_print("  ");
    char y[5];
    itoa(btns->left, y, 10);
    oled_goto_page_column(3,0);
    oled_print(y);
    oled_print("  ");

    CAN_send_extended(BUTTONS, 3, 0, message);
}

void send_touch(Touch *t){
    char message[] = {t->X, t->Y};
    CAN_send_extended(TOUCH, 2, 0, message);

    char X[5];
    itoa(t->X, X, 10);
    oled_goto_page_column(4,0);
    oled_print(X);
    oled_print("  ");
    char y[5];
    itoa(t->Y, y, 10);
    oled_goto_page_column(5,0);
    oled_print(y);
    oled_print("  ");
}

void io_send(){
    Sample s = ADC_sample();
    Joystick j = joystick_read_scale();
    Buttons b = Buttons_read();

    Joystick jstk = {s.joystick_x, s.joystick_y, j.btn};
    Touch t = {s.touch_x, s.touch_y};

    send_joystick(&jstk);
    send_buttons(&b);
    send_touch(&t);
}

CAN_msg1 node2_receive(){
    char message[14];
    CAN_msg1 cm1;
    CAN_read(&message);

    for (int i=0; i<14;i++){
        cm1[i]=message[i];
    }
    return cm1;

}

uint8_t id1 = (cm1.RXB0SIDL>>5);
uint8_t id2 = (cm1.RXB0SIDH<<3);
uint8_t id = id1|id2;