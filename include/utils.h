#pragma once
#define F_CPU 4915200UL
#include <avr/io.h>
#include <util/delay.h>
#include "fonts.h"
#include "string.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/sleep.h>

extern volatile char INT0_FLAG;

extern volatile char CAN_RX_DATA[8];