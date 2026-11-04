#include <stdio.h>
#include <stdarg.h>
#include "can.h"
#include "sam.h"
#include "uart.h"
#include "PWM_driver.h"
#include "ADC_driver.h"
#include "dcmotor.h"
#include "utils.h"
#include "game.h"

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
    uart_init(F_CPU, BAUDRATE); //Uart init
    PWM_init();
    

    
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    //Uncomment after including uart above
    //uart_init(/*cpufreq*/, /*baud*/);
    //printf("Hello World\n\r");
    ADC_init();
    PWM_set(50);
    dcmotor_init();
    motor_PWM_init();
    solenoid_init();
    timer_init();
    int score=0;
    __enable_irq();   // CMSIS, same as "cpsie i"
   //__disable_irq();  // mask all (except NMI/HardFault)
   printf("Lets go");
    while (1){
        if(CAN_FLAG){
            CAN0_Handler_();
            CAN_FLAG = 0;
        }

        if (CT0_FLAG){
            CT0_FLAG=0;
            calculate_thrust();
            if (ADC_sample()<100){
                //end game, Can send back
                CanMsg m;
                m.id=0;
                m.length=1;
                m.byte[0]=1;
                can_tx(m);
                printf("finito");
            }
        }
        
        //calculate_thrust();
        for (int i=0;i<10000;i++){};
        //printf("%d \n\r", REG_TC2_CV0);
    }

    
    
    
}

