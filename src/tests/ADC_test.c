#include "utils.h"
#include "tests/ADC_test.h"
#include "ADC_driver.h"
#include <stdio.h>
void ADC_test(){
    volatile uint8_t *ADC=(uint8_t*)0x1000;
    while (1){
        ADC[0]=1;
        while(PIND & (1<<PD4));
        volatile sample value;
        value=ADC_sample();
        printf("jx=%u ", value.joystick_x);
        printf("jy=%u " , value.joystick_y);
        printf("%u ", value.touch_x);
        printf("%u\n\r ", value.touch_y);
        _delay_ms(500);
    }
    return;
}