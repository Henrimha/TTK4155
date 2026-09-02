#include <avr/io.h>
#include <ATMega162_driver.h>
#include <stdio.h>


void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<URSEL0)|(0<<UMSEL0)|(1<<USBS0)|(1<<UPM01)|(0<<UPM00)|(1<<USBS0)|(3<<UCSZ00); // Akksesser UCSRC registeret. Velger asynkront, even parity. 2 stop bit.  8-bit character size. 


/*
Finne f_osc pga UBRR0H 
U2X = 1 eller 0??
Sette riktig baud rate (9600) 
Sett inn riktig UBRR0H og UBRR0L
*/
 

} //copied from ATmega162 datasheet, page 172

//assumes 8 bit data
void USART_Transmit( unsigned char data)
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) ); // stopper når begge er høye
/* Put data into buffer, sends the data */
UDR0 = data;
} //kopert fra ATmega162 datasheet s 173

/*
sett inn i txd-registeret
indikere at reigisteret er fullt
vente mens vi sender
når sendt indikere at registeret er tomt
klar til nye sendinger

to flagg for tilstand, UDRE og TXC
UDRE: indikerer om bufferet er klart for å motta data
bittet settes når transmitregistert er tomt (1 = tomt/klar, 0 = fullt)
alltid skriv til 0 når man bruker UCSRA-registeret
TXC: er en bit i UCSR0A-registeret

*/
//Documentation
//TODO: can use UDRE, Usart data register empty and TXC transmit complete to generate interrupts

unsigned char USART_Receive()
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}//s176



//recieve complete, RXC, is a flag that indicates that there are unread data present in the recieve buffer. Active high, 1 is data, 0 is no data

//RXCIE in UCSRB can be set to generate interrupt when RC goes high, must clear the RXC flag before interrupt routine terminates

int USART_put(char c, FILE *stream){
    USART_Transmit(c);
    return 0;
}
int USART_get(FILE *stream){
    return (int)USART_Receive();
    
}