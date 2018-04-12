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

extern void pulseLCD();
extern void sendByte(unsigned char, bool);
extern void setCursorPositionLCD(char, char);
extern void clearLCD();
extern void printLCD(unsigned char *);
extern void setBlockCursorLCD();
extern void setLineCursorLCD();
extern void cursorOnLCD();
extern void cursorOffLCD();
extern void displayOffLCD();
extern void displayOnLCD();
extern void homeLCD();
extern void createChar();
extern void initLCD();

#endif /* LIB_DISPLAY_H_ */
