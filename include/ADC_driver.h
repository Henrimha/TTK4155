#pragma once
#include "utils.h"

typedef struct {
    unsigned char joystick_x;
    unsigned char joystick_y;
    unsigned char touch_x;
    unsigned char touch_y;
} sample;

void ADC_init();

static uint8_t scale_axis(uint8_t raw, uint8_t min);

sample ADC_sample();