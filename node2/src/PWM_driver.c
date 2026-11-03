#include "PWM_driver.h"

void PWM_init(){
    // PMC_PCER = (1 << 4);//enable PWM in the PMC
    REG_PMC_PCER1 = PMC_PCDR1_PID36;
    REG_PWM_WPCR = PWM_WPCR_WPKEY(0x50574DUL) | PWM_WPCR_WPCMD(0) | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPRG4;
    

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

}

void PWM_set(uint8_t value){
    int val_min = 0;
    int val_max = 100;
    int max_pwm = 2625;
    int min_pwm = 1313;
    // printf("pwm value: %d\n\n\r", value);

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