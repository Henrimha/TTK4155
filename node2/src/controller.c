#include "controller.h"

void timer_init(){
    REG_PMC_PCER0=PMC_PCER0_PID27;
    REG_TC0_WPMR = RTC_WPMR_WPKEY(0x54494D); //remove write protection

    //TC0-TC2 = ID27-29
    //Lets use TC0
    //COVFS bit in TC_SR is set high when overflow, REG_TC0_SR0 & COVFS
    REG_TC0_CMR0=TC_CMR_TCCLKS_TIMER_CLOCK3|TC_CMR_WAVE|TC_CMR_CPCTRG; // MCK/64, waveform, restart on capture
    REG_TC0_RC0=10938; //120hz

    REG_TC0_IER0|=TC_IER_CPAS; //enable overflow interrupt

    REG_TC0_CCR0=TC_CCR_SWTRG|TC_CCR_CLKEN; //Enable timer and start, timer 0 channel 0
    REG_TC0_WPMR = RTC_WPMR_WPKEY(0x54494D)|RTC_WPMR_WPEN; //add write protection
    PREVIOUS_VALUE=REG_TC2_CV0;
}

ISR(CT0_vect){
    CT0_FLAG=1;
}

//State between 0 and 4000

void calculate_thrust(int ref){
    if(ref>100 || ref<0){
        return;
    }
    int pos = dc_motor_read();
    double K=35;
    double Ti=200000;
    double Td=0.02;

    int e=ref-pos/40;
    int deriv=(pos-PREVIOUS_VALUE);
    int result=K*(e-deriv*Td+INTEGRATOR_STATE/60.0/Ti);
    printf("%d, %d, %d\n\r", result, deriv, INTEGRATOR_STATE/60);

    if (result<-1000){
        result=-1000;

    }
    else if(result>1000){
        result=1000;
    }
    else{
        INTEGRATOR_STATE+=e;
    }
    motor_PWM_set(abs(result), result<=0);
    printf("%d\n\r", result);
    PREVIOUS_VALUE=pos;
    return;
   
    
    //Left is 1
}

// ---------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define REF_MIN          20            /* ref units; keeps the target away from the end stops */
#define REF_MAX          80
#define COUNTS_PER_UNIT  40.0          /* encoder counts per ref unit */
#define TS               (1.0 / 60.0)  /* sample time [s] */
#define OUT_MAX          1000

#define DIR_LEFT         1
#define DIR_RIGHT        0

/* Controller parameters (ideal PID form) */
static const double KP = 10.0;
static const double TI = 1e8;          /* effectively no integral action */
static const double TD = 0.0;

static int    prev_pos   = 0;
static double integrator = 0.0;

void calculate_thrust(int ref)
{
    if (ref < REF_MIN || ref > REF_MAX) {
        return;
    }

    int    pos      = dc_motor_read();
    double error    = ref - pos / COUNTS_PER_UNIT;                 /* ref units */
    double velocity = (pos - prev_pos) / COUNTS_PER_UNIT / TS;     /* ref units/s */
    prev_pos = pos;

    double u = KP * (error - TD * velocity + integrator / TI);

    if (u > OUT_MAX) {
        u = OUT_MAX;                   /* saturated: freeze integrator */
    } else if (u < -OUT_MAX) {
        u = -OUT_MAX;
    } else {
        integrator += error * TS;
    }

    int out = (int)u;

#ifdef DEBUG_THRUST
    printf("%d, %.1f, %.1f\r\n", out, velocity, integrator);
#endif

    motor_PWM_set(abs(out), out <= 0 ? DIR_LEFT : DIR_RIGHT);
}