#include "display.h"

//
// Custom characters
//

const unsigned char customChar[64] = {
0b00010,0b00110,0b01111,0b11111,0b11111,0b01111,0b00110,0b00010,    // 0. Left Arrow
0b01000,0b01100,0b11110,0b11111,0b11111,0b11110,0b01100,0b01000,    // 1. Right Arrow
0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b00000,0b00000,    // 2. Back arrow body
0b01111,0b01111,0b11111,0b11111,0b11111,0b11111,0b00000,0b00000,    // 3. Enter arrow body
0b00100,0b00100,0b01110,0b00000,0b01110,0b01110,0b01110,0b00100,    // 4. Diode
0b00100,0b00010,0b00011,0b00011,0b00111,0b01110,0b11100,0b11000,    // 5. Banana
0b00001,0b00010,0b00100,0b01110,0b00100,0b01000,0b10000,0b00000     // 6. Lightning
};

//
// Pulse the EN bit LOW - HIGH - LOW
// To signal the LCD to accept the data/command
//

void pulseLCD() {
    GPIOPinWrite(CMD_PORT_BASE, EN, 0);
    GPIOPinWrite(CMD_PORT_BASE, EN, EN);
    GPIOPinWrite(CMD_PORT_BASE, EN, 0);
}

//
// Set the RS to LOW
// Indicating incoming command
//

void setCmd() {
    GPIOPinWrite(CMD_PORT_BASE, RS,0);
    delay_ms(1);
}

//
// Set the RS to HIGH
// Indicating incoming data
//

void setData() {
    GPIOPinWrite(CMD_PORT_BASE, RS,RS);
    delay_ms(1);
}

//
// Send data byte in 4 bit mode
// High nibble is sent first
//

void sendByte(unsigned char byteToSend, bool isData) {
    if (isData) setData();
    else setCmd();

    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, byteToSend >> 4);
    pulseLCD();
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, byteToSend);
    pulseLCD();
}

//
// For 16 columns, 2 rows LCD
// Select row / column for next character output
// Initial values are 0,0
//

void setCursorPositionLCD(char col, char row) {
    char address;

    if (row == 0)
        address = 0x80;
    else if (row == 1)
        address = 0xC0;
    else if (row == 2)
        address = 0x94;
    else if (row == 3)
        address = 0xD4;
    else
        address = 0;

    address += col;

    sendByte(address, false);
}

//
// Clear the LCD and return to home position (0,0)
//

void clearLCD() {
    sendByte(0x01, false);
    delay_ms(2);
}

//
// Return to home position (0,0)
//

void homeLCD() {
    sendByte(0x02, false);
    delay_ms(2);
}


//
// Make block cursor visible
//

void setBlockCursorLCD() {
    sendByte(0x0F, false);
}

//
// Make line cursor visible
//

void setLineCursorLCD() {
    sendByte(0x0E, false);
}

//
// Display cursor on screen
//

void cursorOnLCD() {
    sendByte(0x0E, false);
}

//
// Hide cursor from screen
//

void cursorOffLCD() {
    sendByte(0x0C, false);
}

//
// Turn off LCD
//

void displayOffLCD() {
    sendByte(0x08, false);
}

//
// Turn on LCD
//

void displayOnLCD() {
    sendByte(0x0C, false);
}

//
// Print the string on the screen
//

void printLCD(unsigned char *string) {
    while (*string) {
        sendByte(*string++, true);
        //string++;
    }
}

//
// Print the character on the screen
//

void printCharLCD(unsigned char c) {
    sendByte(c, true);
}

//
// Create custom character
// Set CGRAM at 0x40 address
// Print custom characters there
//

void createChar() {
    sendByte(0x40, false);

    for (int i = 0; i < sizeof(customChar) / sizeof(customChar[0]); i++) {
        printCharLCD(customChar[i]);
    }
}

//
// Initialize the LCD
// Performs the following functions:
// Activates selected ports
// Designates ports as outputs
// Pulls all output pins to low
// Waits for LCD warmup
// Sets LCD for 4 pin communication
// Sets two lines display
// Hides the cursor
// Sets insert mode
// Clears the screen
//

void initLCD() {

    //
    // Set the MSP pin configurations and bring them to low
    //

    GPIOPinTypeGPIOOutput(DATA_PORT_BASE,  ALLDATAPINS);
    GPIOPinTypeGPIOOutput(CMD_PORT_BASE, ALLCONTROLPINS);
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS ,0);
    GPIOPinWrite(CMD_PORT_BASE, ALLCONTROLPINS ,0);

    //
    // Initialize the LCM module
    // Set 4-bit input
    //

    setCmd();
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, 0b0010);
    pulseLCD();
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, 0b0010);
    pulseLCD();
    sendByte(0x28, false);  // Set two lines
    cursorOffLCD();         // Cursor invisible
    sendByte(0x06, false);  // Set entry mode
    clearLCD();
    createChar();
}
