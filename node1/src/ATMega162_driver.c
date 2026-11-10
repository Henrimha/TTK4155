#include <avr/io.h>
#include <ATMega162_driver.h>
#include <stdio.h>
#include "MCP2515.h"
#include "mcp2515_driver.h"
#include "utils.h"

void USART_Init( unsigned int ubrr )
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<URSEL0)|(0<<UMSEL0)|(1<<USBS0)|(1<<UPM01)|(0<<UPM00)|(1<<USBS0)|(3<<UCSZ00); // Akksesser UCSRC registeret. Velger asynkront, even parity. 2 stop bit.  8-bit character size.     

} //copied from ATmega162 datasheet, page 172

void interrrupt_init(){
    //Interrupt setup
    DDRD &= ~(1<<PD3);  // PD3/INT1 as input
    MCUCR &= ~((1<<ISC11) | (1<<ISC10));   // INT1 on low level// Interrupt on INT0 is low (falling flank)
    GICR |= (1<<INT1); //Enable interrupt for INT1

    //make counter/timer 0
    TCCR3A = 0; 
    TCCR3B = (1<<CS32)|(1<<CS30)|(1<<WGM32);//Prescaler is 1024, CTC clear timer on compare
    OCR3AH = 1; //Ish 60Hz
    OCR3AL = 5; //5+255
    ETIMSK |= (1<<OCIE3A); //interrupt on output compare A match
    sei();

}

//assumes 8 bit data
void USART_Transmit( unsigned char data)
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) ); // stopper når begge er høye
/* Put data into buffer, sends the data */
UDR0 = data;
} //kopert fra ATmega162 datasheet s 173


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

ISR(INT1_vect){
    INT1_FLAG = 1;
    GICR &= ~(1<<INT1);
}

void int1_interrupt_routine(){
    char error_m = mcp2515_read(MCP_CANINTF);
    //printf("CANINTF = 0x%02X\r\n", error_m);
    if (error_m & 1){
        CAN_read(&CAN_RX_DATA);
    }
    return;
}

ISR(TIMER3_COMPA_vect){
    TC3_FLAG = 1;
    return; //Interrurpt flag is automatily cleared when ISR routine is run
}