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