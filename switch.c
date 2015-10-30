/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include <xc.h>

void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISAbits.TRISA7 = 1;//set switch to input.
        
    CNCONAbits.ON = 1;//ENABLE INTERRUPT
    CNENAbits.CNIEA7 = 1;//enable interrupt of sw1
    IEC1bits.CNAIE = 1;//enable allover interrupt
    IFS1bits.CNAIF = 0;//put flag down
    IPC8bits.CNIP = 7;
//    
    CNPUAbits.CNPUA7 = 1;//ENABLE PULL UP RESISTOR
}

void initSW1(){
    TRISDbits.TRISD13 = 1;// Enable input for switch
    CNCONDbits.ON = 1;       // Turn on CN device
    CNPUDbits.CNPUD13 = 1;// Enable Interal Pull-up resistor
    IPC8bits.CNIP = 7;
    CNENDbits.CNIED13 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    
    
    
}
