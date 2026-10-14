#pragma once
#include "utils.h"
#include "SPI_driver.h"
#include "oled_driver.h"
#include "ADC_driver.h"

typedef enum {
    MAIN_MENU,
    HEAD_MENU,
    // SHOULDER_MENU,
    // KNEE_MENU,
    // TOE_MENU
} States;
// to add sub menus: add menu in the States enum, then add the new stuff like this:
// static const Menu_item eye_items[] = {
//     {"VENSTRE", EYE_MENU},
//     {"HOEYRE",  EYE_MENU},
//     {"TILBAKE", HEAD_MENU},   // back to the parent menu
// };
// #define EYE_ITEM_COUNT (sizeof(eye_items) / sizeof(eye_items[0]))
// then add a case like the others



typedef struct {
    const char *label;
    States target;
} Menu_item;



enum Joystick_states{
    UP,
    NEUTRAL,
    DOWN
};


void menu_state_machine(void);