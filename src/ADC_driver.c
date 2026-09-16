#include "ADC_driver.h"
#include <stdio.h>

void ADC_init(){
    TCCR1B |=(1<<CS10)|(0<<CS11)|(0<<CS12); //No prescaling
    TCCR1B |=(0<<WGM13)|(1<<WGM12);//CTC OCR1A
    TCCR1A |=(0<<WGM11)|(0<<WGM10); //CTC OCR1A
    TCCR1A |= (1<<COM1A0); //Set compare bit to toggle mode
    DDRD |=(1<<PD5); //Set pin D5 to be oupt
    //DDR_OC1A=1; //OCnA value is visble on external pin D5
    OCR1A =10; //Maximum value

    DDRD &=~(1<<PD4);
}
// 200 mikrosekunder
sample ADC_sample(){
    volatile uint8_t *ADC=(uint8_t*)0x1000;
    /*while (1){
    ADC[0]=1; // Write/sample
    _delay_ms(0.5);
    char temp=ADC[0];
    _delay_ms(0.01);
    temp=ADC[0];
    _delay_ms(0.01);
    temp=ADC[0];
    _delay_ms(0.01);
    temp=ADC[0];
    _delay_ms(0.01);
    break;

    }*/
    //while (!(PORTD && (1<<PD4))){}; // wait for busy wait

    /*for (volatile int i=0; i<100;i++){
        printf("%d",PORTD&&(1<<PD4));
    }*/
    ADC[0]=1;
    while(PIND & (1<<PD4));
    volatile sample value;
    value.joystick_x = ADC[0];
    value.joystick_y = ADC[0];
    value.touch_x = ADC[0];
    value.touch_y = ADC[0];
    printf("jx=%u ", value.joystick_x);
    printf("jy=%u " , value.joystick_y);
    printf("%u ", value.touch_x);
    printf("%u\n ", value.touch_y);


    return value;

}