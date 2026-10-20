#include <stdio.h>
#include <stdarg.h>
#include "can.h"
#include "sam.h"
#include "uart.h"
#include "PWM_driver.h"


/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
//#include "../path_to/uart.h"
#define BAUDRATE 9600
#define F_CPU 84000000
int main()
{
    SystemInit();
    WDT->WDT_MR=WDT_MR_WDDIS;
    CanInit init;
    init.sjw=0; //sjw=1
    init.propag=1; //=2
    init.brp=41; //42
    init.phase1=6; //=7
    init.phase2=5; //=6
    init.smp=0; //Sample only once
    can_init(init,1); //interrupts enabled
    uart_init(F_CPU,BAUDRATE); //Uart init
    PWM_init();
    
    
    PMC->PMC_PCER0 |= (1<<ID_PIOB);
    
    PIOB->PIO_PER = PIO_PB13; //Enable register
    PIOB->PIO_OER = PIO_PB13; //output enable register
    
    // PIOB->PIO_SODR = PIO_PB13;  //Setting PB13 High 
    PIOB->PIO_CODR = PIO_PB13;   //clear output data register
    
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    //Uncomment after including uart above
    //uart_init(/*cpufreq*/, /*baud*/);
    //printf("Hello World\n\r");
    
    while (1){

        PWM_set(20);

        for (int i=0;i<1000000;i++){}

        PWM_set(100);
        
        for (int i=0;i<1000000;i++){}


    }

    while (1)
    {
        /* code */
        // Sett PB13 lav
        PIOB->PIO_CODR = PIO_PB13;

        for (volatile unsigned int i = 0; i < 2000000; i++);

        // Sett PB13 høy
        PIOB->PIO_SODR = PIO_PB13;

        for (volatile unsigned int i = 0; i < 2000000; i++);
    }
    
}