#ifndef LIB_BLT_H_
#define LIB_BLT_H_

#include "libraries.h"

#define RX GPIO_PIN_0
#define TX GPIO_PIN_1
#define UART_PINS RX | TX

#define BLT_PORT_BASE GPIO_PORTB_BASE
#define BLT_PERIPH SYSCTL_PERIPH_GPIOB
#define UART1_PERIPH SYSCTL_PERIPH_UART1
#define SERIAL_BUFFER_SIZE 256

typedef struct {
    unsigned char *txBuffer;
    unsigned long txBufferSize;
    unsigned long txWriteIndex;
    unsigned long txReadIndex;
    unsigned char *rxBuffer;
    unsigned long rxBufferSize;
    unsigned long rxWriteIndex;
    unsigned long rxReadIndex;
    int received;
    bool isReceived;
} Bluetooth;

Bluetooth b;

//void setupBluetooth();
//void sendBluetooth(unsigned char *);
//void receiveBluetooth();
void initBluetooth();
void flushAll();
void primeTransmit(unsigned long ulBase);
void setBufferSize(unsigned long, unsigned long);
void end();
int available();
int peek();
int read();
void flush();
size_t write(uint8_t c);

#endif /* LIB_BLT_H_ */
