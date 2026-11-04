#include <utils.h>


volatile char CAN_FLAG=0;

volatile char CAN_RX_DATA[8]={0,0,0,0,0,0,0,0};

volatile char CT0_FLAG=0;

double PREVIOUS_VALUE=0;

double INTEGRATOR_STATE=0;