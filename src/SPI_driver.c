#include "SPI_driver.h"
static void send(char data);
static void send_m(char* sData, size_t len, char* rData);
static void SPI_IO_mode();
static void SPI_CAN_mode();
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
static void send(char cData){
        SPDR = cData;
        while(!(SPSR & (1 << SPIF))); 
    }
char SPI_transmit(char cData, Slaves slave){
    
    switch(slave){
        case(IO_BOARD):
            SPI_IO_mode();
            PORTB &= ~(1 << PB4); // PB4 = CS io board
            send(cData);
            PORTB |= (1<<PB4);
            break;

        case(OLED_SCREEN):
            SPI_IO_mode();
            PORTD &= ~(1 << PD2);
            send(cData);
            PORTD |= (1<<PD2);
            break;
        
        case(CAN_CONTROLLER):
            SPI_CAN_mode();
            PORTB &= ~(1<<PB2);
            send(cData);
            PORTB |=(1<<PB2);
            break;
    }
    return SPDR;
}

static void send_m(char* sData, size_t len, char* rData){
        for (size_t i=0;i<len;i++){
            SPDR = sData[i];
            while(!(SPSR & (1 << SPIF)));
            if (rData!=0){
                rData[i]=SPDR;
            }
        } 
    }

void SPI_array_transmit(char* sData, Slaves slave, size_t len, char* rData){
    
    switch(slave){
        case(IO_BOARD):
            SPI_IO_mode();
            PORTB &= ~(1 << PB4); // PB4 = CS io board
            send_m(sData, len, rData);
            PORTB |= (1<<PB4);
            break;

        case(OLED_SCREEN):
            SPI_IO_mode();
            PORTD &= ~(1 << PD2);
            send_m(sData, len, rData);
            PORTD |= (1<<PD2);
            break;
        
        case(CAN_CONTROLLER):
            SPI_CAN_mode();
            PORTB &= ~(1<<PB2);
            send_m(sData, len, rData);
            PORTB |=(1<<PB2);
            break;
    }
    return;
}


static void SPI_IO_mode(){
    SPCR |=(1<<CPOL);
    
}
static void SPI_CAN_mode(){
    SPCR &= ~(1<<CPOL);
}

Buttons Buttons_read(void){
    Buttons result;
    SPI_IO_mode();
    PORTB &= ~(1<<PB4);
    SPI_shout(0x04);
    _delay_us(40);
    result.right = SPI_shout(0x00);
    _delay_us(2);
    result.left = SPI_shout(0x00);
    _delay_us(2);
    result.nav = SPI_shout(0x00);
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


