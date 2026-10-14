#include "MCP2515.h"
#include "utils.h"


void mcp2515_init();

char mcp2515_read(char adress);
void mcp2515_write(char adress, char data);
char mcp2515_read_status();
void mcp2515_bit_modify(char adress, char mask, char data);