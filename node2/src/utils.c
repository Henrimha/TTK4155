#include <utils.h>


volatile char CAN_FLAG=0;

volatile char CAN_RX_DATA[8]={0,0,0,0,0,0,0,0};

volatile char CT0_FLAG=0;

int PREVIOUS_VALUE=0;

int INTEGRATOR_STATE=0;