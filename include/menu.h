#pragma once
#include "utils.h"
#include "SPI_driver.h"
#include "oled_driver.h"
#include "ADC_driver.h"

enum States{
    MAIN_MENU,
    HEAD_MENU
};

enum Joystick_states{
    UP,
    NEUTRAL,
    DOWN
};


void menu_state_machine();