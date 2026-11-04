#include "menu.h"
#define LEFT_PADDING 10

const Menu_item main_items[] = {
    {"START", MAIN_MENU},
    {"REGULATOR BYTTE", HEAD_MENU},
    {"QUIT", QUIT_MENU},
    // {"NESE", MAIN_MENU}, // to add an option that does not do anything
};
#define MAIN_ITEM_COUNT (sizeof(main_items) / sizeof(main_items[0]))

Menu_item head_items[] = {
    {"POSISJON", HEAD_MENU},
    {"FART", HEAD_MENU},
};
Menu_item quit_items[] = {
    {"TILBAKE", MAIN_MENU},
};
#define HEAD_ITEM_COUNT (sizeof(head_items) / sizeof(head_items[0]))
#define QUIT_ITEM_COUNT (sizeof(quit_items) / sizeof(quit_items[0]))

static void draw_menu(const Menu_item *items, uint8_t count, uint8_t selector){
    for (uint8_t i = 0; i < count; i++){
        oled_goto_page_column(i, LEFT_PADDING);
        oled_print(items[i].label);
    }
    oled_goto_page_column(selector, 0);
    oled_print(">");
}

static uint8_t item_count(States state){
    switch(state){
        case(MAIN_MENU):
            return MAIN_ITEM_COUNT;
        case(HEAD_MENU):
            return HEAD_ITEM_COUNT;
        default: return 1;
    }
}


void menu_state_machine(void){
    States menu_state = MAIN_MENU;
    int selector_position = 0;
    Sample joystick_pos;
    enum Joystick_states joystick_state  = NEUTRAL;
    Buttons buttons;
    Buttons prev_buttons = {0};
    
    while(1){
        joystick_pos = ADC_sample();
        buttons = Buttons_read();

        uint8_t count = item_count(menu_state);
        uint8_t r4_pressed = buttons.R4 && !prev_buttons.R4;
        prev_buttons = buttons;

        // --- Joystick ---
        switch(joystick_state){
            case(UP):
                if(joystick_pos.joystick_y < 60){
                    joystick_state = NEUTRAL;
                }
                break;

            case(NEUTRAL):
                if(joystick_pos.joystick_y > 90){
                    joystick_state = UP;
                    oled_goto_page_column(selector_position, 0);
                    oled_print(" ");
                    if(selector_position == 0){
                        selector_position = count - 1;
                    }else{
                        selector_position--;
                    }
     
                }
                else if(joystick_pos.joystick_y < 10){
                    joystick_state = DOWN;
                    oled_goto_page_column(selector_position, 0);
                    oled_print(" ");
                    selector_position++;
                    if(selector_position >= count){
                        selector_position = 0;
                    }

                }
                break;
            case(DOWN):
                if(joystick_pos.joystick_y > 40){
                    joystick_state = NEUTRAL;
                }
                break;
        }



        switch(menu_state){
            case(MAIN_MENU):
                // trigger
                if(r4_pressed){
                    States next = main_items[selector_position].target;
                    if(next==MAIN_MENU){GAMESTATE=1;}
                    if(next != menu_state){
                        menu_state = next;
                        selector_position = 0;
                        oled_clear();
                    }
                    break;
                }
                // action
                draw_menu(main_items, MAIN_ITEM_COUNT, selector_position);
                break;

            case(HEAD_MENU):
                // trigger
                if(r4_pressed){
                    States next = head_items[selector_position].target;
                    if(next != menu_state){
                        menu_state = next;
                        selector_position = 0;
                        oled_clear();
                    }
                    break;
                }
                // action
                draw_menu(head_items, HEAD_ITEM_COUNT, selector_position);
                break;
            
        }
        if (GAMESTATE){break;};      
    };
    return;
}