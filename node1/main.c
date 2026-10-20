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
#include "oled_driver.h"
#include "menu.h"
#include "tests/joystick_test.h"
#include "CAN_driver.h"
#include "mcp2515_driver.h"
#include "tests/interrupt_test.h"




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
    
    // cli();
    // ADC_test();
    // SRAM_test();
    // oled_print("SuG BalLE og pikk");
    // joystick_test();
    // buttons_test();
    // menu_state_machine();
    // usart_transmit_polling('a');



    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    while(1){
        // Joystick joystick = joystick_read();
        Joystick joystick = joystick_read_scale();

        char message[]={joystick.X,joystick.Y, joystick.btn};
        CAN_send(3, message);
        _delay_ms(500);
    }
    /*
    //CAN test
    while (1){
        char data[9] = "Morten T";
        CAN_send(8, data);
        // int i=0;
        // while (PIND & (1<<PD3)){i++;};
        // CAN_read(data);
        // printf("%s",data);
        _delay_us(1000);


        char data1[9] = "Henrik H";
        CAN_send(8, data1);
        // i=0;
        // while (PIND & (1<<PD3)){i++;};
        // CAN_read(data1);
        // printf("%s",data1);

        _delay_ms(2000);
    }*/

    // char data[9] = "MartinTo";
    // CAN_send(8, data);
    // while (1){
    //     _delay_us(50);

    //     if(INT1_FLAG){
    //         int1_interrupt_routine();
    //         printf("INTT1 ble utløst!!\r\n");
    //         INT1_FLAG=0;
    //         CAN_send(8, data);

    //     }
    //     sleep_enable();
    //     sleep_cpu();  
    //     sleep_disable();
    //     printf("vaaa ble utløst!!\r\n");

    // }
    
    return 0;
}
