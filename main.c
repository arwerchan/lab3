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
    initLCD();
    enableInterrupts();
    initPWM2();
    
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
                clearLCD();
                moveCursorLCD(0, 0);
                currval = (val*3.3) / (1023);
                //testLCD();
                sprintf(string, "%f", currval);
                printStringLCD(string);
                state = wait;
                break;
        }
    }

    return 0;
}

void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void) {
    
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0 * 8;
    //OC4RS = ADC1BUF0;
    val = ADC1BUF0;
    state = print;
    AD1CON1bits.ADON = 0; // turn on the ADC 
}