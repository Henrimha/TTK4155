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
    if(ref>100 || ref<0){
        return 0;
    }
    int kp=1;
    int ki=1;
    int kd=0;

    int e=40*ref-dcmotor_read();
    int diff=dcmotor_read()-PREVIOUS_VALUE;
    int result=kp*e+diff*kd*60+ki*INTEGRATOR_STATE/60;
    if (result<-100){
        result=-100;

    }
    else if(result>100){
        result=100;
    }
    else{
        INTEGRATOR_STATE+=e;
    }
    motor_PWM_set(result, result>=0);

    return;
   
    
    //Left is 1
}