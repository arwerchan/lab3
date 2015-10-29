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
#include "lab3/adc.h"
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"

typedef enum stateTypeEnum {
    scan, print, wait
} stateType;

volatile stateType state = wait;

volatile float val = 0;
volatile float currval = 0;
volatile char* str;

int main(void) {
    SYSTEMConfigPerformance(40000000);
    
    char string[20];
    initADC();
    initTimer2();
    initTimer3();
    initLCD();
    clearLCD();
    enableInterrupts();
    initPWM2();
    initPWM1();
    initPWM3();
    initPWM4();
    
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
        }
    }

    return 0;
}

void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void) {
    
    IFS0bits.AD1IF = 0;
    //
    OC2RS = ADC1BUF0;
    OC3RS = 1023 - ADC1BUF0;
    
    OC5RS = ADC1BUF0;
    OC1RS = 1023 - ADC1BUF0;
    //
    val = ADC1BUF0;
    state = print;
    AD1CON1bits.ADON = 0; // turn on the ADC 
}