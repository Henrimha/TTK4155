// #define F_CPU 16000000
#include <utils.h>
#include <tests/firkantpuls.h>



int main(void) {
    firkantpuls();
    //PORTA &= ~(1 << PA0);
    return 0;
}