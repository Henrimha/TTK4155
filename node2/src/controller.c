#include "controller.h"

void timer_init(){
    REG_PMC_PCER0=PMC_PCER0_PID27;
    REG_TC0_WPMR = RTC_WPMR_WPKEY(0x54494D); //remove write protection

    //TC0-TC2 = ID27-29
    //Lets use TC0
    //COVFS bit in TC_SR is set high when overflow, REG_TC0_SR0 & COVFS
    REG_TC0_CMR0=TC_CMR_TCCLKS_TIMER_CLOCK3|TC_CMR_WAVE|TC_CMR_CPCTRG; // MCK/64, waveform, restart on capture
    REG_TC0_RC0=21875; //60hz

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
    if(ref>80 || ref<20){
        return;
    }
    int pos = dc_motor_read();
    double K=10;
    double Ti=100000000;
    double Td=0;

    int e=ref-pos/40;
    int deriv=(pos-PREVIOUS_VALUE);
    int result=K*(e-deriv*Td+INTEGRATOR_STATE/60/Ti);
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