#include "bluetooth.h"

void setupBluetooth() {

}

void sendBluetooth(unsigned char *string) {
    while (*string) {
        UARTCharPutNonBlocking(UART1_BASE, *string++);
    }
}

void receiveBluetooth() {
    b.isReceived = UARTCharsAvail(UART1_BASE);

    if (b.isReceived) {
        b.received = UARTCharGet(UART0_BASE);
        runMotor("16");
    }
}

void initBluetooth() {

    //
    // Configure PB0 and PB1 as UART
    // 115200 baud, 8-N-1 operation
    //

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(BLT_PORT_BASE, UART_PINS);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
}
