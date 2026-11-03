#include "controller.h"

void timer_init(){
    REG_PMC_PCER0=PMC_PCER0_PID27;
    REG_TC0_WPMR = RTC_WPMR_WPKEY(0x54494D); //remove write protection

    //TC0-TC2 = ID27-29
    //Lets use TC0
    //COVFS bit in TC_SR is set high when overflow, REG_TC0_SR0 & COVFS
    REG_TC0_CMR0=TC_CMR_TCCLKS_TIMER_CLOCK3|TC_CMR_TCCLKS_WAVE|TC_CMR_TCCLKS_CPCTRG; // MCK/64, waveform, restart on capture
    REG_TC0_RC0=21875; //60hz

    REG_TC0_IER0|=TC_IER_CPAS; //enable overflow interrupt

    REG_TC0_CCR0=TC_CCR_SWTRG|TC_CCR_CLKEN; //Enable timer and start, timer 0 channel 0
    REG_TC0_WPMR = RTC_WPMR_WPKEY(0x54494D)|RTC_WPMR_WPEN; //add write protection

}

ISR(CT0_vect){
    
}
void calculate_thrust(){

}