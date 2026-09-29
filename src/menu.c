#include "menu.h"


void menu_state_machine(){
    enum States menu_state = MAIN_MENU;
    int selector_position = 0;
    int left_padding = 10;
    sample joystick_pos;
    enum Joystick_states joystick_state  = NEUTRAL;
    
    while(1){
        joystick_pos = ADC_sample();

        switch(joystick_state){
            case(UP):
                if(joystick_pos.joystick_y < 60){
                    joystick_state = NEUTRAL;
                }
                break;
            case(NEUTRAL):
                if(joystick_pos.joystick_y > 90){
                    joystick_state = UP;

                    for(int i = 0; i < 4; i++){
                        oled_goto_page_column(i,0);
                        oled_print(" ");
                    };
                    selector_position--;
                    if (selector_position < 0){
                        selector_position = 3;
                    }       
                }
                if(joystick_pos.joystick_y < 10){
                    joystick_state = DOWN;

                    for(int i = 0; i < 4; i++){
                        oled_goto_page_column(i,0);
                        oled_print(" ");
                    };
                    selector_position++;
                    if (selector_position > 3){
                        selector_position = 0;
                    }
                }
                break;
            case(DOWN):
                if(joystick_pos.joystick_y > 40){
                    joystick_state = NEUTRAL;
                }
        }



        switch(menu_state){
            case(MAIN_MENU):
                // trigger
                // if(button lav && selector hode)
                //     {
                //         menu_state = HEAD_MENU;
                //         oled_clear();
                //         break;
                //     }

                // action
                oled_goto_page_column(0,left_padding);
                oled_print("HODE");
                oled_goto_page_column(1,left_padding);
                oled_print("SKULDRE");
                oled_goto_page_column(2,left_padding);
                oled_print("KNE");
                oled_goto_page_column(3,left_padding);
                oled_print("TAA");

                oled_goto_page_column(selector_position,0);
                oled_print(">");

            break;

            // case(HEAD_MENU):
            //     // trigger
            //         if(button lav && selector tilbake){
            //             menu_state = MAIN_MENU;
            //             oled_clear();
            //             break;
            //         }

                // action
                oled_goto_page_column(0,left_padding);
                oled_print("OEYNE");
                oled_goto_page_column(1,left_padding);
                oled_print("OERER");
                oled_goto_page_column(2,left_padding);
                oled_print("KINN");
                oled_goto_page_column(3,left_padding);
                oled_print("TILBAKE");

                oled_goto_page_column(selector_position,0);
                oled_print(">");

            break;
        }
    }
}