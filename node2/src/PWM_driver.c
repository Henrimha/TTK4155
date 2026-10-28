#include "PWM_driver.h"

void PWM_init(){
    // PMC_PCER = (1 << 4);//enable PWM in the PMC
    REG_PMC_PCER1 = PMC_PCDR1_PID36;
    REG_PWM_WPCR = PWM_WPCR_WPKEY(0x50574DUL) | PWM_WPCR_WPCMD(0) | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPRG4;
    // (0x50574DUL << PWM_WPCR_WPKEY_Pos);  //PWM in ascii
    // REG_PWM_WPCR |= PWM_WPCR_WPRG2; //sRegister 2 disable, PCMR osv
    // REG_PWM_WPCR |= PWM_WPCR_WPRG3; //sRegister 3 disable, CPRD
    // REG_PWM_WPCR |= PWM_WPCR_WPRG4; //sRegister 4 disable, Dead time osv
    // REG_PWM_WPCR &= ~(1 << PWM_WPCR_WPCMD_Pos); // Disable write protection 
    // REG_PWM_WPCR &= ~(1 << PWM_WPCR_WPCMD_Pos+1); // Disable write protection 

    // set peripherals
    REG_PIOB_PDR = PIO_PB13; // disable peripheral registoer io pb13
    REG_PIOB_ABSR |= PIO_PB13; // select register peripheral pb13


    // PWM_CLK |= (1<< PWM_CLK_DIVA_Pos);  //Deler ikke på DIV, bare PRA (2-ern)
    // PWM_CLK |= (0b0110 << PWM_CLK_PREA_Pos); //deler på 64
    REG_PWM_CMR1 &= ~0xF;
    REG_PWM_CMR1 |= PWM_CMR_CPRE_MCK_DIV_64;
    REG_PWM_CMR1 &= ~PWM_CMR_CALG; // Left alligment
    REG_PWM_CMR1 |= PWM_CMR_CPOL; //Start at high level
    REG_PWM_CMR1 &= ~PWM_CMR_CES; // trlig irrelevant:)  counter event selection
    REG_PWM_CMR1 &= ~PWM_CMR_DTE; // disable Dead time

    REG_PWM_CPRD1 = 26250; //Øvre grense for 
    REG_PWM_CDTY1 = 1969; //Starter i midten
    REG_PWM_SCM &= ~PWM_SCM_SYNC1; // Ikke synkron channel
    REG_PWM_SCM &= ~(1<<PWM_SCM_UPDM_Pos); // The WRDY flag and the PDC transfer request are never set to 1.
    REG_PWM_SCM &= ~(1<<PWM_SCM_UPDM_Pos+1); //The WRDY flag and the PDC transfer request are never set to 1.


    // Husk å sette pins fra I/O til PWM
    // PA8= PWMH0 
    // PA9 = PWMH3
    // PB13 = PWMH1
    // REG_PWM_ENA=(1<<CHID1); //enable channel register 
    REG_PWM_ENA = PWM_ENA_CHID1;
    // REG_PIOB_PER = PIO_PB13;
    REG_PWM_WPCR = PWM_WPCR_WPKEY(0X50574DUL) | PWM_WPCR_WPCMD(1) | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPRG4;
    // REG_PWM_WPCR |= (1 << PWM_WPCR_WPCMD_Pos); // enable write protection 
    // REG_PWM_WPCR &= ~(1 << PWM_WPCR_WPCMD_Pos+1); // enable write protection 




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

void PWM_set(uint8_t value){
    int val_min = 0;
    int val_max = 100;
    int max_pwm = 2625;
    int min_pwm = 1313;

    int duty_cycle; //1125
    if (value > val_max){
        duty_cycle = max_pwm;
    }
    else if (value < val_min){
        duty_cycle = min_pwm;
    }
    else {
        duty_cycle = value * (max_pwm - min_pwm)/(val_max - val_min) + min_pwm;
    }
    // printf("%d", duty_cycle);
    REG_PWM_CDTYUPD1 = duty_cycle;
    // printf("  wm_set\n");

}