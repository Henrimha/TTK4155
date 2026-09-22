#include "SPI_driver.h"

void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
/* Enable SPI, Master, set clock rate fck/2, Interrupt disabled (0), 
MSB first, SCK is high when idle (leading edge is falling, trailing is rising),
Setup on trailing/rising edge, sample on leading/falling*/
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPRI2X)|(0<<SPIE)|(0<<DORD)|(1<<CPOL)|(0<<CPHA);

}
void SPI_MasterTransmit(char cData)
{
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)))
;
}//Copied from datasheet

//Need to set the direction of SS pin, as an output
//If set as an input, when driven low, it automaticly sets itself as slave