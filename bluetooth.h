#ifndef LIB_BLT_H_
#define LIB_BLT_H_

#include "libraries.h"

#define RX GPIO_PIN_0
#define TX GPIO_PIN_1
#define UART_PINS RX | TX

#define BLT_PORT_BASE GPIO_PORTB_BASE
#define BLT_PERIPH SYSCTL_PERIPH_GPIOB
#define UART1_PERIPH SYSCTL_PERIPH_UART1

typedef struct {
    unsigned int received;
    bool isReceived;
} Bluetooth;

Bluetooth b;
void setupBluetooth();
void sendBluetooth(unsigned char *);
//void receiveBluetooth();
void initBluetooth();

#endif /* LIB_BLT_H_ */
