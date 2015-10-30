#include <xc.h>
#include "PWM.h"

#define off 0x0

/*void initPWM1() {
    //ODC3
    RPF1Rbits.RPF1R = 0b1011; // map RF1 pin 8 of J11 to OC3
    OC3CON = 0x0000; // Turn off on OC3
    OC3R = 0X0000; // Initialize primary compare register
    OC3RS = 0X0000; // Initialize secondary compare register
    OC3CON = 0x0006; // Configure for PWM mode
    OC3CONbits.OCTSEL = 1;
    OC3CONbits.ON = 1; // Enable OC3
}*/

/*void initPWM2() {
    //ODC2
    RPD1Rbits.RPD1R = 0b1011; // map RD1 pin 20 of J11 to OC2
    OC2CON = 0x0000; // Turn off OC2
    OC2R = 0X0000; // Initialize primary compare register
    OC2RS = 0X0000; // Initialize secondary compare register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONbits.OCTSEL = 1;
    OC2CONbits.ON = 1; // Enable OC3
}*/

void initPWM3() {
    //ODC5
    RPD9Rbits.RPD9R = 0b1011; // map RD9 pin 26 of J11 to OC5
    OC5CON = 0x0000; // Turn off OC5
    OC5R = 0X0000; // Initialize primary compare register
    OC5RS = 0X0000; // Initialize secondary compare register
    OC5CON = 0x0006; // Configure for PWM mode
    OC5CONbits.OCTSEL = 1;
    OC5CONbits.ON = 1; // Enable OC5
}

void initPWM4() {
    //ODC1
    RPD5Rbits.RPD5R = 0b1100; // map RD5 pin 13 of J10 to OC1
    OC1CON = 0x0000; // Turn off OC1
    OC1R = 0X0000; // Initialize primary compare register
    OC1RS = 0X0000; // Initialize secondary compare register
    OC1CON = 0x0006; // Configure for PWM mode
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.ON = 1; // Enable OC1
}