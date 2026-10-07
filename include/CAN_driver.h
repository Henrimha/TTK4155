#pragma once

#include "utils.h"
#include "SPI_driver.h"
#include "MCP2515.h"


void CAN_init();
void CAN_read(char* rData);
void CAN_send(char* rData);
