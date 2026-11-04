// #define F_CPU 16000000
#include <utils.h>
#include <tests/firkantpuls.h>
#include <tests/usart_polling.h>
#include <stdio.h>
#include <ATMega162_driver.h>
#include <tests/sram_test.h>
#include <SRAM_driver.h>
#include <ADC_driver.h>
#include <tests/ADC_test.h>
#include <SPI_driver.h>
#include "include/menu.h"
#include "oled_driver.h"
#include "menu.h"
#include "tests/joystick_test.h"
#include "CAN_driver.h"
#include "mcp2515_driver.h"
#include "tests/interrupt_test.h"
#include "game.h"

//ADC sample bruker 320 us
//UART uses 1ms approx, per byte
//SPI uses 104.3 us
//CAN bus is 47 + 8*n bits, up to 25 bit stuffing. 8 us per bit
//SRAM maybe 0.5us


// #define FOSC 1843200// Clock Speed
#define FOSC 4915200UL// Clock Speed

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
// volatile uint8_t can_interrupt_flag = 0;

// ISR(INT1_vect)
// {
//     can_interrupt_flag = 1;
// }


int main(void) {
    fdevopen(USART_put, USART_get);
    USART_Init(MYUBRR);
    ADC_init();
    external_memory_init();
    SPI_Init();
    oled_init();
    mcp2515_init();
    CAN_init();
    interrrupt_init();
    // interrupt_test();
    printf("shallom allekom");
    
    cli(); //Fjerner interrupts???
    // ADC_test();
    // SRAM_test();
    // oled_print("SuG BalLE og pikk");
    // joystick_test();
    // buttons_test();
    // menu_state_machine();
    // usart_transmit_polling('a');



    set_sleep_mode(SLEEP_MODE_PWR_SAVE);



    while(1){
        menu_state_machine();

        while(1){
            io_send();
            if(INT1_FLAG){
                INT1_FLAG=0;
                int1_interrupt_routine();
                printf("Tilbake til State Maskin!!\r\n");
                break;
            }
        }
    }
    

    // char data[9] = "MartinTo";
    // CAN_send(8, data);
    // while (1){
    //     _delay_us(50);

    //     
    //     sleep_enable();
    //     sleep_cpu();  
    //     sleep_disable();
    //     printf("vaaa ble utløst!!\r\n");

    // }
    
    return 0;
}
