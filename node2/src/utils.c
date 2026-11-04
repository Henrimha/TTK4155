#include <utils.h>


volatile char CAN_FLAG=0;

// volatile char CAN_RX_DATA[8]={0,0,0,0,0,0,0,0};

volatile CanMsg CAN_RX_DATA;


volatile char CT0_FLAG=0;

volatile int REF=0;