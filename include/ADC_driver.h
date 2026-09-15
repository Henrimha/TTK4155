#include "utils.h"

typedef struct {
    char joystick_x;
    char joystick_y;
    char touch_x;
    char touch_y;
} sample;

void ADC_init();

sample ADC_sample();