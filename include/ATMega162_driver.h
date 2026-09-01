#pragma once
#include <utils.h>

#define baud F_CPU/(16*(UBRR+1))

void USART_Init( unsigned int ubrr );

void USART_Transmit( unsigned char data );

//void USART_Transmit( unsigned int data );

unsigned char USART_Receive( void );

//unsigned int USART_Receive( void );
