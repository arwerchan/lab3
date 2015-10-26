/*
 * File:   lcd.c
 * Authors: Hongning Shangguan
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define LCD_E  LATDbits.LATD1
#define LCD_RS   LATDbits.LATD9

#define TRIS_D7  TRISEbits.TRISE7
#define TRIS_D6  TRISEbits.TRISE5
#define TRIS_D5  TRISEbits.TRISE3
#define TRIS_D4  TRISEbits.TRISE1
#define TRIS_E   TRISDbits.TRISD1
#define TRIS_RS  TRISDbits.TRISD9

#define LAT_4 LATEbits.LATE1
#define LAT_5 LATEbits.LATE3
#define LAT_6 LATEbits.LATE5
#define LAT_7 LATEbits.LATE7
#define LOWER 0
#define UPPER 1
#define LCD_WRITE_DATA   1
#define LCD_CONTROL_DATA 0
#define ON 0
#define OFF 1

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower) {
    //TODO:
    if (lower == LOWER) {
        LAT_7 = (word & 0x08) >> 3;
        LAT_6 = (word & 0x04) >> 2;
        LAT_5 = (word & 0x02) >> 1;
        LAT_4 = (word & 0x01);

    } else if (lower == UPPER) {

        LAT_7 = (word) >> 7;
        LAT_6 = (word << 1) >> 7;
        LAT_5 = (word << 2) >> 7;
        LAT_4 = (word << 3) >> 7;


    }
    LCD_RS = commandType; //D3
    delayUs(1);
    LCD_E = 1;
    delayUs(1); //
    LCD_E = 0; // D5
    delayUs(delayAfter);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter) {
    //TODO:
    writeFourBits(word, commandType, delayAfter, UPPER);
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c, LCD_WRITE_DATA, 46);
}

/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).

    TRIS_D4 = ON;
    TRIS_D5 = ON;
    TRIS_D6 = ON;
    TRIS_D7 = ON;
    TRIS_RS = ON;
    TRIS_E = ON;
    // Initilization sequence utilizes specific LCD commands before the general configuration    
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    // Enable 4-bit interface
    int i;
    for(i = 0; i < 100; i ++) delayUs(150);

    writeFourBits(0x03, LCD_CONTROL_DATA, 4100, LOWER);

    writeFourBits(0x03, LCD_CONTROL_DATA, 100, LOWER);

    writeLCD(0x32, LCD_CONTROL_DATA, 40);

    writeLCD(0x28, LCD_CONTROL_DATA, 40);
    // TODO: Display On/Off Control

    writeLCD(0x08, LCD_CONTROL_DATA, 40);
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.

    writeLCD(0x01, LCD_CONTROL_DATA, 1640);

    // TODO: Entry Mode Set

    writeLCD(0x06, LCD_CONTROL_DATA, 40);
    // TODO: Display On/Off Control
    writeLCD(0x0C, LCD_CONTROL_DATA, 40);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {

    //TODO:
    int i;
    for (i = 0; i < strlen(s); i++) {
        printCharLCD(s[i]);

    }
}

/*
 * Clear the display.
 */
void clearLCD() {
    writeLCD(0x01, LCD_CONTROL_DATA, 1640);
    moveCursorLCD(0, 0);

}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 * x row y colum 
 */
void moveCursorLCD(unsigned char x, unsigned char y) {

    if (x == 0) {
        writeLCD(0x80 + y, LCD_CONTROL_DATA, 40);

    }
    if (x == 1) {
        writeLCD(0xC0 + y, LCD_CONTROL_DATA, 40);
    }

}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD() {
    int i = 0;
    printCharLCD('c');
    for (i = 0; i < 250; i++) delayUs(1000);
    clearLCD();
    for (i = 0; i < 250; i++) delayUs(1000);
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for (i = 0; i < 250; i++) delayUs(1000);
    printStringLCD("Hello!");
    for (i = 0; i < 250; i++) delayUs(1000);
    clearLCD();
    
}

