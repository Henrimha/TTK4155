#include "utils.h"

typedef struct {
    unsigned char joystick_x;
    unsigned char joystick_y;
    unsigned char touch_x;
    unsigned char touch_y;
} sample;

void ADC_init();

sample ADC_sample();