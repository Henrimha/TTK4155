#pragma once
#include "utils.h"
#include "SPI_driver.h"
#include "fonts.h"
void oled_init(void);

void oled_reset(void);

void oled_home(void);

void oled_goto_page_column(uint8_t page, uint8_t column);

static inline void oled_command(char data){ oled_transmit(data,1);};

static inline void oled_data(char data){ oled_transmit(data,0);};
 
void oled_home();

void oled_char( char letter);

void oled_print( char text[]);

void oled_clear();
