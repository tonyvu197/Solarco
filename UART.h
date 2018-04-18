#ifndef LIB_SRL_H_
#define LIB_SRL_H_

#include "libraries.h"

#define RX GPIO_PIN_0
#define TX GPIO_PIN_1
#define UART_PINS RX | TX
#define UART1_PORT_BASE GPIO_PORTB_BASE
#define UART1_PORT_PERIPH SYSCTL_PERIPH_GPIOB
#define UART1_PERIPH SYSCTL_PERIPH_UART1

typedef struct {
    bool run;
    unsigned char recv[3];
} UART1;

volatile UART1 u;

extern void initUART1();
extern void UART1receive();
extern void disableUART1();
extern void enableUART1();
extern void blueMotor();
extern void UART1send(const unsigned char *);

#endif /* LIB_SRL_H_ */
