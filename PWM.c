#include <xc.h>
#include "PWM.h"

#define off 0x0

void initPWM1() {
    //ODC1
    RPD1Rbits.RPD1R = 0b1011; // map RD1 to OC1
    OC1CON = 0x0000; // Turn off OC1
    OC1R = 0X0000; // Initialize primary compare register
    OC1RS = 0X0000; // Initialize secondary compare register
    OC1CON = 0x0006; // Configure for PWM mode
    OC1CONSET = 0x8000; // Enable OC1
}

void initPWM2() {
    //ODC2
    RPD1Rbits.RPD1R = 0b1011; // map RD0 to OC2
    OC2CON = 0x0000; // Turn off OC2
    OC2R = 0X0000; // Initialize primary compare register
    OC2RS = 0X0000; // Initialize secondary compare register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC2
}
