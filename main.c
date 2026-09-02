// #define F_CPU 16000000
#include <utils.h>
#include <tests/firkantpuls.h>
#include <tests/usart_polling.h>
#include <stdio.h>
#include <ATMega162_driver.h>
// #define FOSC 1843200// Clock Speed
#define FOSC 4915200UL// Clock Speed

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void) {
    fdevopen( USART_put, USART_get);
    firkantpuls();
    USART_Init(MYUBRR);
    //usart_transmit_polling('a');
   

    //PORTA &= ~(1 << PA0);
    return 0;
}
// SPørs,ålsliste: 
// F0SC vs F_CPU
// 


// kortslutt
// finn parity og stopbits til usart 