#pragma once
#include "utils.h"


void SPI_MasterInit(void);

char SPI_Transmit(char cData);

char button_read(void);

void Oled_transmit(char data, int command);
