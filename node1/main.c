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
    
     //Fjerner interrupts???
    // ADC_test();
    SRAM_test();
    // oled_print("SuG BalLE og pikk");
    // joystick_test();
    // buttons_test();
    // menu_state_machine();
    // usart_transmit_polling('a');



    //set_sleep_mode(SLEEP_MODE_PWR_SAVE);


    int fet=0;
    while(1){
        fet=0;
        menu_state_machine();
        GAMESTATE=0;
        oled_clear();
            // drop anything stale from the previous game
        mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00);
        INT1_FLAG = 0;
        GIFR = (1<<INTF1);
        GICR |= (1<<INT1);
        while(1){
            if(INT1_FLAG){
                cli();
                INT1_FLAG=0;
                int1_interrupt_routine();
                sei();
                //printf("Tilbake til State Maskin!!\r\n");
                break;
            }
            if (TC3_FLAG){
                cli();
                TC3_FLAG=0;
                io_send();

                fet++;
                if (!(fet%30)){
                    char y[5];
                    itoa(fet/30, y, 10);
                    oled_goto_page_column(7,0);
                    oled_print(y);
                    oled_print("    ");
                }
                sei();
                //System routine
            }
        }
        oled_clear();
    }
    
   
   
    
    return 0;
}
