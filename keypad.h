#ifndef LIB_KEYPAD_H_
#define LIB_KEYPAD_H_

#include "libraries.h"

#define KEYPAD_ROW_1 GPIO_PIN_4 // The row beginning with 1
#define KEYPAD_ROW_2 GPIO_PIN_5 // The row beginning with 4
#define KEYPAD_ROW_3 GPIO_PIN_6 // The row beginning with 7
#define KEYPAD_ROW_4 GPIO_PIN_7 // The row beginning with *
#define KEYPAD_ROWS KEYPAD_ROW_1 | KEYPAD_ROW_2 | KEYPAD_ROW_3 | KEYPAD_ROW_4

#define KEYPAD_COL_1 GPIO_PIN_2 // The column beginning with 1
#define KEYPAD_COL_2 GPIO_PIN_3 // The column beginning with 2
#define KEYPAD_COL_3 GPIO_PIN_4 // The column beginning with 3
#define KEYPAD_COLS KEYPAD_COL_1 | KEYPAD_COL_2 | KEYPAD_COL_3

#define ROW_PORT_BASE GPIO_PORTC_BASE // ROW pins connect to port C
#define COL_PORT_BASE GPIO_PORTA_BASE // COL pins connect to port A
#define KEYPAD_ROW_PERIPH SYSCTL_PERIPH_GPIOC
#define KEYPAD_COL_PERIPH SYSCTL_PERIPH_GPIOA

typedef struct {
    unsigned char *keyPressed;
    int row, col;
    bool isPressed;
} Key;

volatile Key k;

extern void readKeypad();
extern void getKeypad(unsigned char *);
extern void initKeypad();

#endif /* LIB_KEYPAD_H_ */
