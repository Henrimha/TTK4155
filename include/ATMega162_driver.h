#pragma once
#include <utils.h>
#include <stdio.h>

#define baud F_CPU/(16*(UBRR+1))

void USART_Init( unsigned int ubrr );

void USART_Transmit( unsigned char data);

int USART_put(char c, FILE *stream);
int USART_get(FILE *stream);


unsigned char USART_Receive( void );

