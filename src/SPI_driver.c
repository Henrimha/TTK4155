#include "SPI_driver.h"
void SPI_MasterInit(void)
{
//Set the SS pin to be output pin
DDRB|=(1<<PB4)|(1<<PB7)|(1<<PB5); //Buttons CS, SCK, MOSI: are output

// Interrupt disabled (0), Enable SPI, MSB first, Master, clock polarity, clock phase, set clock rate fck/2
//SCK is high when idle (leading edge is falling, trailing is rising),
//Setup on trailing/rising edge, sample on leading/falling
SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);
SPSR|=(1<<SPI2X);
DDRB &= ~(1<<PB6); //MISO: Set input
PORTB|=(1<<PB4); //set high, becuse active low
DDRD|=(1<<PD2)|(1<<PD3); //OLED CS, D/C# are outputs
PORTD|=(1<<PD2); //Set high, because active low


}
char SPI_Transmit(char cData)
{
/* Start transmission, SPDR is read write register */
SPDR = cData;
/* Wait for transmission complete , SPIF is flag for done with transmission*/
while(!(SPSR & (1<<SPIF)))
;
return SPDR;
}//Copied from datasheet

//Need to set the direction of SS pin, as an output
//If set as an input, when driven low, it automaticly sets itself as slave

void Oled_transmit(char data, int command){
    if (command){
        PORTD &= ~(1<<PD3);
    }
    else {
        PORTD |=(1<<PD3);
    }
    PORTD &= ~(1<<PD2); 
    SPI_Transmit(data);
    PORTD |= (1<<PD2);
    return;
}

char button_read(void){
    PORTB &= ~(1<<PB4);
    char result=SPI_Transmit('a'); //dummy value
    PORTB |= (1<<PB4);
    return result;
}