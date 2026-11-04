#include "controller.h"



void TC0_Handler(void){
    volatile uint32_t sr = REG_TC0_SR0;
    CT0_FLAG=1;
    NVIC_ClearPendingIRQ(ID_TC0);
}

//State between 0 and 4000
#define REF_MIN 0 // ref units; keeps the target away from the end stops 
#define REF_MAX 110
#define COUNTS_PER_UNIT 40.0  // encoder counts per ref unit 
#define TS (1.0 / 120.0) // sample time [s] 
#define OUT_MAX 800

#define DIR_LEFT 1
#define DIR_RIGHT 0
/* Controller parameters (ideal PID form) */
static const double KP = 20.0;
static const double TI = 1;          /* effectively no integral action */
static const double TD = 0.0;

static int    prev_pos   = 0;
static double integrator = 0.0;
static int check=0;
void calculate_thrust(){
   check++;
    if(!(check%1000)){printf("%d\r\n",REF);}
    if (REF < REF_MIN || REF > REF_MAX) {
        return;
    }

    int pos = dc_motor_read();
    double error = REF - pos / COUNTS_PER_UNIT;
    double velocity = (pos - prev_pos) / COUNTS_PER_UNIT / TS; 
    prev_pos = pos;
    double u = KP * (error - TD * velocity + integrator / TI);

    if(u > OUT_MAX){
        u = OUT_MAX;                   /* saturated: freeze integrator */
    }
    else if(u < -OUT_MAX){
        u = -OUT_MAX;
    }else{
        integrator += error * TS;
    }
    int out = (int)u;

    motor_PWM_set(abs(out), out <= 0 ? DIR_LEFT : DIR_RIGHT);
    //printf("%d\n\r", result);
    return;
   
}

void timer_init(){
    REG_PMC_PCER0=PMC_PCER0_PID27;
    REG_TC0_WPMR = TC_WPMR_WPKEY(0x54494D); //remove write protection

    //TC0-TC2 = ID27-29
    //Lets use TC0
    //COVFS bit in TC_SR is set high when overflow, REG_TC0_SR0 & COVFS
    REG_TC0_CMR0=TC_CMR_TCCLKS_TIMER_CLOCK3|TC_CMR_WAVE|TC_CMR_CPCTRG; // MCK/32, waveform, restart on capture
    REG_TC0_RC0=21875; //120hz

    REG_TC0_IER0|=TC_IER_CPCS; //enable overflow interrupt
    NVIC_EnableIRQ(TC0_IRQn);
    REG_TC0_CCR0=TC_CCR_SWTRG|TC_CCR_CLKEN; //Enable timer and start, timer 0 channel 0
    REG_TC0_WPMR = TC_WPMR_WPKEY(0x54494D)|RTC_WPMR_WPEN; //add write protection
    prev_pos=REG_TC2_CV0;
}