
#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"

volatile double val;
volatile double currval = 0;
volatile char * str;

int main(void){
    SYSTEMConfigPerformance(40000000);
    
    initLCD();
    initADC();
    initTimer2();
    initPWM();
    enableInterrupts();
    
    while(1){
        moveCursorLCD (0, 0);
        currval = (val*3.3) / (65536);
        sprintf(str, "%f", currval);
        printStringLCD(str);
    }
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7AUTP) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
    OC4RS = ADC1BUF0;
    val = ADC1BUF0;
}