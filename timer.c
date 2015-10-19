/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>


//Uses timer 2

void delayUs(unsigned int delay) {
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR2 = 0; //clear timer 2
    PR2 = (delay * 5) - 1;
    IFS0bits.T2IF = 0; //put flag down
    T2CONbits.ON = 1; //turn on timer 2
    while (IFS0bits.T2IF == 0) {
    };
    T2CONbits.ON = 0; //stop timer 2
}

void initTimer2() {
    //TODO: Initialize Timer 2.
    TMR2 = 0; //clear timer 2
    T2CONbits.TCKPS = 3; //initial prescalar to 8
    T2CONbits.TCS = 0; //setting the oscillator
    IPC2bits.T2IP=7;// configure the interrupt priority 
    IFS0bits.T2IF = 0; //put flag down

}