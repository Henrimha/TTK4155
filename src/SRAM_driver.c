#include <avr/io.h>
#include <stdio.h>
#include <SRAM_driver.h>



void external_memory_init (){
    MCUCR = (1 << SRE); // Enable external memory
    SFIOR = (1 <<XMM2)|(0<<XMM1)|(0<<XMM0);

}
//PC0 = A_8
//PC1 = A_9
// PC2 = A_11
// PC3 = A_10

// Sjekk om PC3 ==0 eller 1. Hvis 1 gå til SRAM hvis 0 gå til ADC.