#pragma once
#include <utils.h>

#define baud F_CPU/(16*(UBRR+1))

void USART_Init( unsigned int ubrr );

void USART_Transmit( unsigned char data );


unsigned char USART_Receive( void );

