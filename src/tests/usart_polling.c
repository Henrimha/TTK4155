#include "tests/usart_polling.h"
#include <ATMega162_driver.h>

void usart_transmit_polling(unsigned char c){
    
    while (1){
            USART_Transmit(c);
            _delay_ms(100);
            printf("halla balla");
        }
    }
