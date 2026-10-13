#pragma once

#include "utils.h"
#include "SPI_driver.h"
#include "MCP2515.h"


void CAN_init();
void CAN_read(char* rData);
void CAN_send_extended(uint16_t identifier, char length, char RTR, char *sData);
static inline void CAN_send(char length, char *sData){CAN_send_extended(0x01, length, 0, sData);};
