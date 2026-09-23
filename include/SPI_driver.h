#pragma once
#include "utils.h"


void SPI_Init(void);

char SPI_Transmit(char cData);

char button_read(void);

void oled_transmit(char data, int command);
