#include <avr/io.h>
#include <stdio.h>
#include <SRAM_driver.h>



void external_memory_init (){
    MCUCR |= (1 << SRE); // Enable external memory
    SFIOR |= (1 <<XMM2)|(0<<XMM1)|(0<<XMM0);

}
//PC0 = A_8
//PC1 = A_9
// PC2 = A_11
// PC3 = A_10

// Sjekk om PC3 ==0 eller 1. Hvis 1 gå til SRAM hvis 0 gå til ADC.

// hvis ADC har aktiv høy CS må signalet gjennom NAND før til chip select.


// stemmer rekkefølgen med at først wr og cs lav, så vente på bw høy (med interrupt eller polling?), så cs og rd lav? Ja
// clk. fra oscillatoren til atmegaen eller sin egen eller gnd (som på bildet). clk signal fra atmega
