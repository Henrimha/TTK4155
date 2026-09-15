#include "ADC_driver.h"
#include <stdio.h>

void ADC_init(){
    TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12); //No prescaling
    TCCR1B|=(0<<WGM13)|(1<<WGM12);//CTC OCR1A
    TCCR1A|=(0<<WGM11)|(0<<WGM10); //CTC OCR1A
    TCCR1A|= (1<<COM1A0); //Set compare bit to toggle mode
    DDRD|=(1<<PD5); //Set pin D5 to be oupt
    //DDR_OC1A=1; //OCnA value is visble on external pin D5
    OCR1A=10; //Maximum value
}
// 200 mikrosekunder
sample ADC_sample(){
    volatile uint8_t *ADC=(uint8_t*)0x1000;
    ADC[0]=1; // Write/sample

    
    while (PORTD & (1<<PD4)){ // fiks løkka
        
    } // Wait for the toggle to go low, indicating that the sample is done
    volatile sample value;
    value.joystick_x = ADC[0];
    value.joystick_y = ADC[0];
    value.touch_x = ADC[0];
    value.touch_y = ADC[0];
    printf("%d ", value.joystick_x);
    printf("%d ", value.joystick_y);
    printf("%d ", value.touch_x);
    printf("%d\n", value.touch_y);

    return value;

}