#include "ADC_driver.h"

void ADC_init(){
    TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12) //No prescaling
    TCCR1B|=(0<<WGM13)|(1<<WGM12)//CTC OCR1A
    TCCR1A|=(0<<WGMn1)|(0<<WGMn0) //CTC OCR1A
    TTCR1A|= (1<<COM1A1) //Set compare bit to toggle mode
    DDRD|=(1<<PD5) //Set pin D5 to be oupt
    //DDR_OC1A=1 //OCnA value is visble on external pin D5
    OCR1A=0 //Maximum value
}

int ADC_sample(){

}