#include "ADC_driver.h"
#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
void ADC_init(){ //ADC er ID nr 37
    REG_PMC_PCER1=PMC_PCER1_PID37; //Enable ADC
    REG_ADC_CR = ADC_CR_SWRST; //Hardware reset
    REG_ADC_WPMR = ADC_WPMR_WPKEY(0x414443); //Set write protect to 0
    //There is a minimal startup time
    //Set PMC
    REG_ADC_MR =ADC_MR_TRGEN_DIS | ADC_MR_LOWRES_BITS_10 | ADC_MR_SLEEP_NORMAL | ADC_MR_PRESCAL(2) 
    | ADC_MR_STARTUP_SUT8 | ADC_MR_SETTLING_AST9 | ADC_MR_ANACH_NONE | ADC_MR_USEQ_NUM_ORDER | ADC_MR_TRACKTIM(15) | ADC_MR_TRANSFER(2);//Hardware triggers disabled 
    
    //enable by writing ADC_CHER
    REG_ADC_CHER = ADC_CHER_CH0;

    //No interrupts
    REG_ADC_IDR = 0xffffffff; //Disable all interrupts
    //Bruke PIN A0/PA2  , eller AD0, Channel 0

    //ADVREF?? set the reference externally

    //STores value in ADC_CDRx, ADC_LCDR

    //There are flags to check if values are overwritten
    REG_ADC_WPMR |= ADC_WPMR_WPKEY(0x414443)|ADC_WPMR_WPEN; //set write protect to 1, on
}

int ADC_sample(){
    REG_ADC_CR |= ADC_CR_START; //Start analog to digital conversion
    //Wait
    int i=0;
    while( !(REG_ADC_ISR & ADC_ISR_EOC0)){
        i++; 
        if (i>1000000){printf("Timout"); 
            return 9999;}
    } //Wait for conversion to finish
    return ADC->ADC_CDR[0] & ADC_CDR_DATA_Msk; //value stored

}
