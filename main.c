// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "PWM.h"
#include "adc.h"
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "switch.h"
#define SW PORTGbits.RG13
#define press 0
#define release 1
#define enableForward LATDbits.LATD12
#define enableBackward LATDbits.LATD6
#define output 0
#define input 1



typedef enum stateTypeEnum {
    scan, print, wait, forward, backward
} stateType;

volatile stateType state = wait;

volatile float val = 0;
volatile float currval = 0;
volatile char* str;
volatile int index = 0;

int main(void) {
     
    TRISDbits.TRISD6 = output;
    TRISDbits.TRISD12 = output;
    index = 0;
     
    SYSTEMConfigPerformance(40000000);
    
    char string[20];
    initADC();
    initTimer2();
    initTimer3();
    initLCD();
    clearLCD();
    initSW2();
    initSW1();
   // initPWM2();
   // initPWM1();
    initPWM3();
    initPWM4();
    enableInterrupts();
    
    AD1CON1bits.ADON = 0; // turn on the ADC 

    while (1) {
        switch(state) {
            case wait:
                state = scan;
                break;
            case scan:
                AD1CON1bits.ADON = 1; // turn on the ADC 
                break;
            case print:
                moveCursorLCD(0, 0);
                currval = (val*3.3) / (1023);
                sprintf(string, "%.2f", currval);
                printStringLCD(string);
                state = wait;
                break;
                
            case forward:
                enableBackward = 0;
                enableForward = 1;
                index = 1;
                state = wait;
                break;
                
            case backward:
                enableBackward = 1;
                enableForward = 0;
                index = 0;
                state = wait;
                break;
                
        }
    }

    return 0;
}

void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void) {
    
    IFS0bits.AD1IF = 0;
    //
  //if(index == 1){
      //OC5RS = 0;
      //OC1RS = 0;
//    if(ADC1BUF0 < 612 && ADC1BUF0 > 412){
//        OC3RS = 1023;
//        OC2RS = 1023;
//    }
//    else if(ADC1BUF0 >= 612){
//        OC3RS = 1023 - ADC1BUF0;
//        OC2RS = 1023;
//    }
//    else if(ADC1BUF0 <= 412){
//        OC3RS = 1023;
//        OC2RS = ADC1BUF0;
//    }
 // }
  //else{
    //  OC2RS = 0;
      //OC3RS = 0;
    if(ADC1BUF0 < 612 && ADC1BUF0 > 412){
        OC5RS = 1023;
        OC1RS = 1023;
    }
    else if(ADC1BUF0 >= 612){
        OC5RS = 1023 - ADC1BUF0;
        OC1RS = 1023;
    }
    else if(ADC1BUF0 <= 412){
        OC5RS = 1023;
        OC1RS = ADC1BUF0;
    }
 // }
    //
    val = ADC1BUF0;
    state = print;
    AD1CON1bits.ADON = 0; // turn on the ADC 
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    int dummy;
    dummy = SW;
    IFS1bits.CNGIF = 0;
    IFS1bits.CNDIF = 0;
    if(SW == press && index == 1){
        state = backward;
    }
    else if(SW == press && index == 0){
        state = forward;
    }
}