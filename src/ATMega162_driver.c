#include 
#include <avr/io.h>


void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRRH = (unsigned char)(ubrr>>8);
UBRRL = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN);
/* Set frame format: 8data, 2stop bit */
UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
} //copied from ATmega162 datasheet, page 172

//assumes 8 bit data
void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) )
;
/* Put data into buffer, sends the data */
UDR = data;
} //kopert fra ATmega162 datasheet s 173

//Assumes 9 bit data
/*
void USART_Transmit( unsigned int data )
{
// Wait for empty transmit buffer 
while ( !( UCSRA & (1<<UDRE)) )
;
// Copy 9th bit to TXB8 
UCSRB &= ~(1<<TXB8);
if ( data & 0x0100 )
UCSRB |= (1<<TXB8);
// Put data into buffer, sends the data 
UDR = data;
}*/

//TODO: can use UDRE, Usart data register empty and TXC transmit complete to generate interrupts

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSRA & (1<<RXC)) )
;
/* Get and return received data from buffer */
return UDR;
}//s176

/*unsigned int USART_Receive( void )
{
unsigned char status, resh, resl;
// Wait for data to be received 
while ( !(UCSRA & (1<<RXC)) )
;
// Get status and 9th bit, then data 
// from buffer
status = UCSRA;
resh = UCSRB;
resl = UDR;
// If error, return -1 
if ( status & (1<<FE)|(1<<DOR)|(1<<UPE) )
return -1;
// Filter the 9th bit, then return 
resh = (resh >> 1) & 0x01;
return ((resh << 8) | resl);
} //s177*/

//recieve complete, RXC, is a flag that indicates that there are unread data present in the recieve buffer. Active high, 1 is data, 0 is no data

//RXCIE in UCSRB can be set to generate interrupt when RC goes high, must clear the RXC flag before interrupt routine terminates