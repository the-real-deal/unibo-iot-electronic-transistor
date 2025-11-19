#ifndef LCD_H
#define LCD_H

/*
 * Function to setup the LCD
 */
void setupLcd();

/*
 * Function to print multiple lines to the LCD
 * Parameters:
 *  - int nRows: number of rows to print
 *  - ...: variable arguments representing the lines to print
 */
void printToLcd(const int nRows, ...);

#endif