#include "SPI_driver.h"
void SPI_Init(void)
{
//Set the SS pin to be output pin
DDRB|=(1<<PB4)|(1<<PB7)|(1<<PB5); //Buttons CS, SCK, MOSI: are output

// Interrupt disabled (0), Enable SPI, MSB first, Master, clock polarity, clock phase, set clock rate fck/2
//SCK is high when idle (leading edge is falling, trailing is rising),
//Setup on trailing/rising edge, sample on leading/falling
SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
SPSR |= (1<<SPI2X);
DDRB &= ~(1<<PB6); //MISO: Set input
PORTB|=(1<<PB4); //set high, becuse active low
DDRD|=(1<<PD2)|(1<<PD3); //OLED CS, D/C# are outputs
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
char SPI_Transmit(char cData)
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
        PORTD &= ~(1<<PD3);
    }
    else {
        PORTD |=(1<<PD3);
    }
    PORTD &= ~(1<<PD2); 
    char temp=SPI_Transmit(data);
    PORTD |= (1<<PD2);
    return temp;
}

char SPI_master_transmit(char cData, Slaves slave){
    switch(slave){
        case(IO_BOARD):
            PORTB &= ~(1 << PB4); // PB4 = CS io board
            PORTD |= (1 << PD2); // PD2 = CS oled display
            break;

        case(OLED_SCREEN):
            PORTD &= ~(1 << PD2);
            PORTB |= (1 << PB4);
            break;
    }
    SPDR = cData;
    while(!(SPSR & (1 << SPIF)));   
    return SPDR;
}


char IO_transmit(char data){
    PORTB &= ~(1<<PB4);
    char result=SPI_Transmit(data); 
    PORTB |= (1<<PB4);
    return result;
}

void SPI_write(char data, int slave){ //slave=0 => oled, 1 => IO board
    if (slave==0){
        oled_transmit(data,0);
    }
    else if (slave==1){
        IO_transmit(data);
    }
}
char SPI_read(int slave){
    if (slave==0){
        return oled_transmit('a',0);
    }
    else if(slave==1){
        return IO_transmit('a');
    }
}
char SPI_readNwrite(char data, int slave){
    if (slave==0){
        return oled_transmit(data,0);
    }
    else if (slave==1){
        return IO_transmit(data);
    }


}

Buttons Buttons_read(void){
    Buttons result;
    PORTB &= ~(1<<PB4);
    SPI_master_transmit(0x04, IO_BOARD);
    _delay_us(40);
    result.right = SPI_master_transmit(0x00, IO_BOARD);
    _delay_us(2);
    result.left = SPI_master_transmit(0x00, IO_BOARD);
    _delay_us(2);
    result.nav = SPI_master_transmit(0x00, IO_BOARD);
    PORTB |= (1<<PB4);

    return result;

}

void LED_enable(int LED_N, uint8_t state){
    IO_transmit(0x05);
    IO_transmit(LED_N);
    IO_transmit(state);
}
void LED_PWM(int LED_N, uint8_t width){    PORTB |= (1<<PB4);

    IO_transmit(0x06);
    IO_transmit(LED_N);
    IO_transmit(width); //0 to 255
}

Joystick joystick_read (void){
    Joystick joystick;
    PORTB &= ~(1<<PB4);
    SPI_Transmit(0x03);
    _delay_us(80);
    joystick.X = SPI_Transmit(0x00);
    _delay_us(15);
    joystick.Y = SPI_Transmit(0x00);
    _delay_us(15);
    joystick.btn = SPI_Transmit(0x00);
    PORTB |= (1<<PB4);

    return joystick;
}

char CAN_transmit(char data){
    
}
