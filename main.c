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
    interrupt_test();
    printf("shallom allekom");
    
    // cli();
    // ADC_test();
    // SRAM_test();
    // oled_print("SuG BalLE og pikk");
    // joystick_test();
    // buttons_test();
    // menu_state_machine();
    // usart_transmit_polling('a');



    // set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    // while (1){
    //     char data[9] = "Martin T";
    //     CAN_send(8, data);
    //     int i=0;
    //     while (PIND & (1<<PD3)){i++;};
    //     CAN_read(data);
    //     printf("%s",data);


    //     char data1[9] = "Henrik H";
    //     CAN_send(8, data1);
    //     i=0;
    //     while (PIND & (1<<PD3)){i++;};
    //     CAN_read(data1);
    //     printf("%s",data1);

    //     _delay_ms(100);
    // }

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
// SPørs,ålsliste: 
// F0SC vs F_CPU


// kortslutt
// finn parity og stopbits til usart 

// 1. Lag klokkesignal
//2. Bli 100% sikker på at ingeting må initsialiseres på ADC Tror at analoget signale tar alle samtidig. HVa skjer når Read=1 
// 3. Dobbeltsjekke at de analogesignalene sendes til riktig sted. 
//4. Funksjonene med Busy og fire read og eller write. 


//4. Kalibrer 



// sjekke om klokkesignal generator funker, hvis ikke spr chat
// lag funskjoner som henter ut data eller sampler fra joystick ting
//print verdiene til skjerm

// LATCH
// PE1 = ALE som skal inn i LE på latchen
// LE er høy => outputs Q = data inputs på D
// LE lav => outputs Q = det som er lagra (ikke på D)
// OE høy => High impedance Q, sender ingenting
// OE lav => fungerer som normalt

// SRAM
// Har 8K adresser. ATmega har 64K adresser. Begge har registerstørrelse på 8 bits
// PA0-PA7 skal inn i LATCH D-porter
// PC0-PC7 skal inn i SRAM. bruker PC4-PC7 til JTAG
    // kan ikke bruke 16 bit til adresse => 12 bits isedet
// PD6 er write signal. WE lav => skriv data. WE høy => Output disabled/Read data
// PD7 er read signal. OE (output enable) lav => les data. OE høy => output disabled
// A_0-A_12 er adressebits. A_12 brukes ikke, må groundes
// I/O_0-I/O_7 er data input/output



// ocrna er min 0x0003 (2 bits)
// tcntn 