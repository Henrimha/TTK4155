#include "tests/firkantpuls.h"

void firkantpuls(){
    DDRA |= (1 << PA0);

    while(1){
        PORTA |= (1 << PA0);
        _delay_ms(1000);
        PORTA &= ~(1<<PA0);
        _delay_ms(1000);
    }
    return;
}