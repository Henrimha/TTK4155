#include "PWM_driver.h"

void PWM_init(){
    PMC_PCER1 = (1 << 4);//enable PWM in the PMC
    PWM_WPCR |= (0x50574DUL << PWM_WPCR_WPKEY_Pos);  //PWM in ascii
    PWM_WPCR |= PWM_WPCR_WPRG0; //sKlokke skløtte register
    PWM_WPCR &= ~(1 << PWM_WPCR_WPCMD_Pos); // Disable write protection

    // PWM_CLK |= (1<< PWM_CLK_DIVA_Pos);  //Deler ikke på DIV, bare PRA (2-ern)
    // PWM_CLK |= (0b0110 << PWM_CLK_PREA_Pos); //deler på 64
    PWM_CMR0 &= ~0xF;
    PWM_CMR0 |= PWM_CMR_CPRE_MCK_DIV_64;
    PWM_CMR0 &= ~(1<< PWM_CMR_CALG); // Left alligment
    PWM_CMR0 |= (1 << PWM_CMR_CPOL); //Start at high level
    PWM_CMR0 &= ~(1 << PWM_CMR_CES); // trlig irrelevant:)  counter event selection
    PWM_CMR0 &= ~(1 << PWM_CMR_DTE); // disable Dead time

    PWM_CPRD1 = 25 000; //Øvre grense for 
     







    // Husk å sette pins fra I/O til PWM
    // PA8= PWMH0 
    // PA9 = PWMH3
    // PB13 = PWMH1
    PWM_ENA=(1<<CHID1); //enable channel register 1




    /*
    Unlock User Interface by writing the WPCMD field in the PWM_WPCR Register.
     Configuration of the clock generator (DIVA, PREA, DIVB, PREB in the PWM_CLK register if required).
     Selection of the clock for each channel (CPRE field in the PWM_CMRx register)
     Configuration of the waveform alignment for each channel (CALG field in the PWM_CMRx register)
     Selection of the counter event selection (if CALG = 1) for each channel (CES field in the PWM_CMRx
    register)
     Configuration of the output waveform polarity for each channel (CPOL in the PWM_CMRx register)
     Configuration of the period for each channel (CPRD in the PWM_CPRDx register). Writing in PWM_CPRDx
    register is possible while the channel is disabled. After validation of the channel, the user must use
    PWM_CPRDUPDx register to update PWM_CPRDx as explained below.
     Configuration of the duty-cycle for each channel (CDTY in the PWM_CDTYx register). Writing in
    PWM_CDTYx register is possible while the channel is disabled. After validation of the channel, the user
    must use PWM_CDTYUPDx register to update PWM_CDTYx as explained below.
     Configuration of the dead-time generator for each channel (DTH and DTL in PWM_DTx) if enabled (DTE bit
        in the PWM_CMRx register). Writing in the PWM_DTx register is possible while the channel is disabled.
    After validation of the channel, the user must use PWM_DTUPDx register to update PWM_DTx
     Selection of the synchronous channels (SYNCx in the PWM_SCM register)
     Selection of the moment when the WRDY flag and the corresponding PDC transfer request are set (PTRM    and PTRCS in the PWM_SCM register)
     Configuration of the update mode (UPDM in the PWM_SCM register)
     Configuration of the update period (UPR in the PWM_SCUP register) if needed.
     Configuration of the comparisons (PWM_CMPVx and PWM_CMPMx).
     Configuration of the event lines (PWM_ELMRx).
     Configuration of the fault inputs polarity (FPOL in PWM_FMR)
     Configuration of the fault protection (FMOD and FFIL in PWM_FMR, PWM_FPV and PWM_FPE/2)
     Enable of the Interrupts (writing CHIDx and FCHIDx in PWM_IER1 register, and writing WRDYE, ENDTXE,    TXBUFE, UNRE, CMPMx and CMPUx in PWM_IER2 register)
     Enable of the PWM channels (writing CHIDx in the PWM_ENA register)
    */
}