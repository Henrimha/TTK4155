#pragma once
#include "utils.h"
#include "SPI_driver.h"
void oled_init(void);

void oled_reset(void);

void oled_home(void);

void oled_goto_line(uint8_t line);

static inline void oled_command(char data){ oled_transmit(data,1);};

static inline void oled_data(char data){ oled_transmit(data,0);};
 
void oled_home();
