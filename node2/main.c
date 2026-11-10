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
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
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
    ADC_init();
    dcmotor_init();
    motor_PWM_init();
    solenoid_init();
    timer_init();

    __enable_irq();   // CMSIS, same as "cpsie i"
   //__disable_irq();  // mask all (except NMI/HardFault)
   printf("Init successfull");
   //reset_encoder();
   printf("reset_done");
    PWM_set(50);

    while (1){
        

        if (CT0_FLAG){
            CT0_FLAG=0;
            if(JOYSTICK_FLAG){
                __disable_irq();
                CanMsg m = JOYSTICK_MSG;
                JOYSTICK_FLAG = 0;
                __enable_irq();
                joystick_control(&m);
            }

            if(TOUCH_FLAG){
                __disable_irq();
                CanMsg m = TOUCH_MSG;
                TOUCH_FLAG=0;
                __enable_irq();
                touch_control(&m);

            }
            if(BUTTONS_FLAG){
                __disable_irq();
                CanMsg m = BUTTONS_MSG;
                BUTTONS_FLAG=0;
                __enable_irq();
                buttons_control(&m);

            }
            //calculation:
            __disable_irq();
            calculate_thrust();
            if (ADC_sample()<100){
                //end game, Can send back
                CanMsg m={0};
                m.id=0; m.length=1; m.byte[0]=1;
                can_tx(m);
                //printf("finito");
                //reset_encoder();
            }
            __enable_irq();

            if(solenoid_ticks){
                if(--solenoid_ticks == 0){
                    REG_PIOA_SODR = PIO_PA23;     // pin high = off
                }
            }
            else if(solenoid_cooldown){
                solenoid_cooldown--;
            }
        }
        
        //calculate_thrust();
        //printf("%d \n\r", REG_TC2_CV0);
    }

    
    
    
}

