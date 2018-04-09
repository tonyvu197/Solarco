#ifndef LIB_DISPLAY_H_
#define LIB_DISPLAY_H_

#include "libraries.h"

#define RS GPIO_PIN_1
#define EN GPIO_PIN_2
#define D4 GPIO_PIN_0
#define D5 GPIO_PIN_1
#define D6 GPIO_PIN_2
#define D7 GPIO_PIN_3
#define ALLDATAPINS  D7 | D6 | D5 | D4
#define ALLCONTROLPINS RS | EN

#define DATA_PORT_BASE GPIO_PORTD_BASE  // Data pins connect to port D
#define CMD_PORT_BASE GPIO_PORTE_BASE   // Command pins connect to port E
#define LCD_DATA_PERIPH SYSCTL_PERIPH_GPIOD
#define LCD_CMD_PERIPH SYSCTL_PERIPH_GPIOE

void pulseLCD();
void sendByte(unsigned char, bool);
void setCursorPositionLCD(char, char);
void clearLCD();
void printLCD(unsigned char *);
void setBlockCursorLCD();
void setLineCursorLCD();
void cursorOnLCD();
void cursorOffLCD();
void displayOffLCD();
void displayOnLCD();
void homeLCD();
void createChar();
void initLCD();

#endif /* LIB_DISPLAY_H_ */
