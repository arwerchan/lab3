// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"

#define input 1
#define output 0
#define pin1 LATBbits.LATB4
#define pin2 PORTDbits.RD6
#define pin3 LATBbits.LATB2
#define pin4 PORTDbits.RD12
#define pin5 LATBbits.LATB0
#define pin6 PORTFbits.RF1
#define pin7 PORTGbits.RG0
#define press 0
#define release 1
#define scanning 1
#define notscan 0

typedef enum stateTypeEnum {
    Wait, Scan, Print, MoveCursor, debounce1, debounce2
} stateType;
volatile stateType state;
volatile int key = -1;
volatile int count = 0;

int main(void) {
    
    SYSTEMConfigPerformance(40000000);
    initKeypad();
    enableEnterruptKeypad();
    initTimer2();
    initLCD();
    enableInterrupts();
    moveCursorLCD(0,0);
    state = Wait;

    while (1) {
        switch (state) {
            case Wait:
                break;

            case Scan:
                key = scanKeypad();
                state = MoveCursor;
                break;
                
            case MoveCursor:
                if(count == 0) moveCursorLCD(0,0);
                else if (count == 9) moveCursorLCD(1,0);
                state = Print;
                break;
                
            case debounce1:
                delayUs(500);
                state = Scan;
                break;
                
            case debounce2:
                delayUs(500);
                state = MoveCursor;
                break;

            case Print:
                delayUs(100);
                if(key == 0) printCharLCD('0');
                else if(key == 1) printCharLCD('1');
                else if(key == 2) printCharLCD('2');
                else if(key == 3) printCharLCD('3');
                else if(key == 4) printCharLCD('4');
                else if(key == 5) printCharLCD('5');
                else if(key == 6) printCharLCD('6');
                else if(key == 7) printCharLCD('7');
                else if(key == 8) printCharLCD('8');
                else if(key == 9) printCharLCD('9');
                else if(key == 10) printCharLCD('*');
                else if(key == 11) printCharLCD('#');
                state = Wait;
                break;

        }
    }

    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    int dummy;
    if (CNSTATDbits.CNSTATD6 == 1) dummy = pin2;
    if (CNSTATDbits.CNSTATD12 == 1) dummy = pin4;
    if (CNSTATFbits.CNSTATF1 == 1) dummy = pin6;
    if (CNSTATGbits.CNSTATG0 == 1) dummy = pin7;
    IFS1bits.CNFIF = 0;
    IFS1bits.CNDIF = 0;
    IFS1bits.CNGIF = 0;
    
    if(state == Wait && (pin2==press||pin4==press||pin6==press||pin7==press)){
        count ++;
        if(count == 18) count = 0;
        
    }
    
    if (state == Wait) state = debounce1;
    else if (state == Scan) state = debounce2;
}