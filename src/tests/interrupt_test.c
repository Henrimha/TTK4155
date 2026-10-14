#include "tests/interrupt_test.h"

void interrupt_test(){
    char data[9] = "MartinTo";
    CAN_send(8, data);
    while (1){
        _delay_us(50);
        
        if(INT1_FLAG){
            int1_interrupt_routine();
            printf("INT1 ble utløst!!\r\n");
            INT1_FLAG=0;
            CAN_send(8, data);
            
        }
        sleep_enable();
        sleep_cpu();  
        sleep_disable();
        printf("vaaa ble utløst!!\r\n");
        
    }
}
    