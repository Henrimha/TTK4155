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

// #define FOSC 1843200// Clock Speed
#define FOSC 4915200UL// Clock Speed

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void) {
    fdevopen(USART_put, USART_get);
    // // firkantpuls();
    USART_Init(MYUBRR);
    ADC_init();
    external_memory_init();
    //SRAM_test();
    SPI_MasterInit();
    //ADC_test();

    while(1){
        printf("%c",button_read());
        Oled_transmit('h',0);

    }
    //usart_transmit_polling('a');
   

    //PORTA &= ~(1 << PA0);
    return 0;
}
// SPørs,ålsliste: 
// F0SC vs F_CPU
// 


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