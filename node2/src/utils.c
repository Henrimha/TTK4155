#include <utils.h>


//volatile char CAN_FLAG=0;

// volatile char CAN_RX_DATA[8]={0,0,0,0,0,0,0,0};

volatile CanMsg CAN_RX_DATA;


volatile char CT0_FLAG=0;

volatile int REF=0;

volatile char JOYSTICK_FLAG=0;
volatile CanMsg JOYSTICK_MSG={0};

volatile char TOUCH_FLAG=0;
volatile CanMsg TOUCH_MSG={0};

volatile char BUTTONS_FLAG=0;
volatile CanMsg BUTTONS_MSG={0};