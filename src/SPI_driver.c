#include "SPI_driver.h"
void SPI_Init(void)
{
//Set the SS pin to be output pin
DDRB|=(1<<PB4)|(1<<PB7)|(1<<PB5)|(1<<PB3)|(1<<PB2); //Buttons CS, SCK, MOSI, D/C#, MCP2515 CS: are output

// Interrupt disabled (0), Enable SPI, MSB first, Master, clock polarity, clock phase, set clock rate fck/2
//SCK is high when idle (leading edge is falling, trailing is rising),
//Setup on trailing/rising edge, sample on leading/falling
SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
SPSR |= (1<<SPI2X);
DDRB &= ~(1<<PB6); //MISO: Set input
PORTB|=(1<<PB4)|(1<<PB2); //set high, becuse active low
DDRD|=(1<<PD2); //OLED CS is output
PORTD|=(1<<PD2); //Set high, because active low


// SPI clock 
// SPCR |= (1 << SPR0);
// SPCR &= ~(1 << SPR1);
// SPSR &= ~(1 << SPI2X);

// SPCR &= ~(1 << SPIE); //
// SPCR |= (1 << SPE);
// SPCR &= ~(1 << DORD);
// SPCR |= (1 << MSTR);
// SPCR |= (1 << CPOL);
// SPCR &= ~(1 << CPHA);

}
char SPI_shout(char cData)
{
/* Start transmission, SPDR is read write register */
SPDR = cData;
/* Wait for transmission complete , SPIF is flag for done with transmission*/
while(!(SPSR & (1<<SPIF)));
return SPDR;
}//Copied from datasheet

//Need to set the direction of SS pin, as an output
//If set as an input, when driven low, it automaticly sets itself as slave

char oled_transmit(char data, int command){
    if (command){
        PORTB &= ~(1<<PB3);
    }
    else {
        PORTB |=(1<<PB3);
    }
    
    return SPI_transmit(data, OLED_SCREEN);
}

char SPI_transmit(char cData, Slaves slave){
    auto send = [](char cData){
        SPDR = cData;
        while(!(SPSR & (1 << SPIF))); 
    }
    switch(slave){
        case(IO_BOARD):
            PORTB &= ~(1 << PB4); // PB4 = CS io board
            send(cData)
            PORTB |= (1<<PB4);
            break;

        case(OLED_SCREEN):
            PORTD &= ~(1 << PD2);
            send(cData);
            PORTD |= (1<<PD2);
            break;
        
        case(CAN_CONTROLLER):
            PORTB &= ~(1<<PB2);
            send(cData);
            PORTB |=(1<<PB2);
            break;
    }
    return SPDR;
}

/*
char CAN_transmit(char data){
    PORTB &= ~(1<<PB4);
    char result = SPI_Transmit(data);
    PORTB |= (1<<PB4);
    return result;
}

char IO_transmit(char data){
    PORTB &= ~(1<<PB4);
    char result=SPI_Transmit(data); 
    PORTB |= (1<<PB4);
    return result;
}*/

Buttons Buttons_read(void){
    Buttons result;
    PORTB &= ~(1<<PB4);
    SPI_transmit(0x04, IO_BOARD);
    _delay_us(40);
    result.right = SPI_transmit(0x00, IO_BOARD);
    _delay_us(2);
    result.left = SPI_transmit(0x00, IO_BOARD);
    _delay_us(2);
    result.nav = SPI_transmit(0x00, IO_BOARD);
    PORTB |= (1<<PB4);

    return result;

}

void LED_enable(int LED_N, uint8_t state){
    IO_transmit(0x05);
    IO_transmit(LED_N);
    IO_transmit(state);
}
void LED_PWM(int LED_N, uint8_t width){  

    IO_transmit(0x06);
    IO_transmit(LED_N);
    IO_transmit(width); //0 to 255
}

Joystick joystick_read (void){
    Joystick joystick;
    PORTB &= ~(1<<PB4);
    SPI_shout(0x03);
    _delay_us(80);
    joystick.X = SPI_shout(0x00);
    _delay_us(15);
    joystick.Y = SPI_shout(0x00);
    _delay_us(15);
    joystick.btn = SPI_shout(0x00);
    PORTB |= (1<<PB4);

    return joystick;
}


