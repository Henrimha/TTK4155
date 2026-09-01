// #define F_CPU 16000000
#include <utils.h>
#include <tests/firkantpuls.h>
#include <ATMega162_driver.h>
#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void) {
    //firkantpuls();
    USART_Init(MYUBRR);
    //PORTA &= ~(1 << PA0);
    return 0;
}