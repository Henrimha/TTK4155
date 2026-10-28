#include "dcmotor.h"

void dcmotor_init(){
    // io pins
    //TC2 har id 33
    REG_PMC_PCER1 = PMC_PCER1_PID33; //Enable CT2
    REG_PIOC_PDR |= PIO_PC25; // disable peripheral registoer io pc25
    REG_PIOC_PDR |= PIO_PC26; // disable peripheral registoer io pc26
    REG_PIOC_ABSR |= PIO_PC25; // select register peripheral pb13
    REG_PIOC_ABSR |= PIO_PC26; // select register peripheral pb13
    // quadrature decoder
    // Sette tioa0 og tiob0 til input
    REG_TC2_WPMR = RTC_WPMR_WPKEY(0x54494D);
    REG_TC2_QIDR = 7;  //disables all interrupts
    REG_TC2_CMR0 |= TC_CMR_TCCLKS_XC0;
    REG_TC2_BMR |= TC_BMR_QDEN; // Enable quadrature decoding
    REG_TC2_CMR0 &= ~TC_CMR_WAVE; //CH0 and CH1 is in capture mode
    REG_TC2_CMR0 |= TC_CMR_ETRGEDG_RISING; //Rising edge is selected as the external trigger
    REG_TC2_CMR0 |= TC_CMR_ABETRG; //A is set as external trigger
    // Må bruke enten position eller speed
    REG_TC2_BMR |= TC_BMR_POSEN; // Measure position
    // TC_BMR |= TC_BMR_SPEEDEN; // Measure speed

    REG_TC2_BMR &= ~TC_BMR_QDTRANS; // enable direction change detected
    REG_TC2_BMR |= TC_BMR_EDGPHA; // Detect edges pn both TIOA0 and TIOB0
    REG_TC2_BMR &= ~TC_BMR_INVA; // Inverter positiv retning TIOA0
    REG_TC2_BMR &= ~TC_BMR_INVB; // Inverter positiv retning TIOAB0
    REG_TC2_BMR &= ~TC_BMR_SWAP; // Ikke bytt pha og phb
    REG_TC2_BMR |= TC_BMR_MAXFILT(20); // filter mellom 1 og 63 T_grense = (maxfilt + 1) * T_clock
    REG_TC2_CCR0 = TC_CCR_CLKEN|TC_CCR_SWTRG;
    REG_TC2_WPMR = RTC_WPMR_WPKEY(0x54494D)|RTC_WPMR_WPEN;

}

void dc_motor_reset(){
    REG_TC2_CCR0 = TC_CCR_SWTRG;

}

int dc_motor_read(){
    return REG_TC2_CV0;
}

void motor_PWM_init(){
    // Supply a voltage to the 4mm banana sockets (9V - 12V)
    // Apply a PWM signal to the ENABLE/PWM pin (any frequency below 50 kHz)
    // Apply a high or low signal to the PHASE/DIR pin
    // The ENABLE/PWM pin is connected to Arduino pin D20, or ATSAM3X8E pin PB12. 
    REG_PWM_WPCR = PWM_WPCR_WPKEY(0x50574DUL) | PWM_WPCR_WPCMD(0) | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPRG4;

    REG_PIOB_PDR |= PIO_PB12; // disable peripheral registoer io pc26
    REG_PIOB_ABSR |= PIO_PB12; // select register peripheral pb12

    REG_PWM_CMR0 &= ~0xF;
    REG_PWM_CMR0 |= PWM_CMR_CPRE_MCK_DIV_2;
    REG_PWM_CMR0 &= ~PWM_CMR_CALG; // Left alligment
    REG_PWM_CMR0 |= PWM_CMR_CPOL; //Start at high level
    REG_PWM_CMR0 &= ~PWM_CMR_CES; // trolig irrelevant:)  counter event selection
    REG_PWM_CMR0 &= ~PWM_CMR_DTE; // disable dead time
    REG_PWM_SCM &= ~PWM_SCM_SYNC0; // Ikke synkron channel
    REG_PWM_CPRD0 = 2100; //Øvre grense for 
    REG_PWM_CDTY0 = 0; //Starter med 0 i power

    REG_PWM_ENA = PWM_ENA_CHID0;

    //PWM out on PB12 is set with alternate function B on PIOB, and frequency/duty cycle is set on PWM channel 0
    //Use PWMH0

    //The PHASE/DIR pin is connected to Arduino pin D7, or ATSAM3X8E pin PC23.
    REG_PIOC_WPMR=PIO_WPMR_WPKEY(0x50494F);
    REG_PIOC_PER =PIO_PC23; //disable pheripherals, enable PIO
    REG_PIOC_OER = PIO_PC23;//set as output
    REG_PIOC_OWER = PIO_PC23; //Can use ODSR to set the line
    REG_PIOC_WPMR=PIO_WPMR_WPKEY(0x50494F) | PIO_WPMR_WPEN;

}

void motor_PWM_set(u_int32_t value, char dir_left){
    if (value>2100){
        REG_PWM_CDTYUPD1=2100;
    }
    else{
        REG_PWM_CDTY0 = value; 
    }
    if (dir_left){
        REG_PIOC_SODR = PIO_PC23; //set data to ouput 23
    }
    else {
        REG_PIOC_CODR = PIO_PC23; //set data to ouput 23

    }
    //Set phase


}