#include "tests/usart_polling.h"
#include <ATMega162_driver.h>

void usart_transmit_polling(unsigned char c){
    char a='b';
    while (1){
        
            USART_Transmit(c);
            _delay_ms(100);
            printf("hello world ");
            while (a!='a'){
                USART_Transmit(a);
                a=USART_Receive();
            }
            a='b';

        }
    }
