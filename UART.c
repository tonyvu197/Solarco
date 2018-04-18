#include "UART.h"

//
// Check flag to run the motor
//

void blueMotor() {
    disableUART1();
    clearLCD();
    setCursorPositionLCD(0, 0);
    printLCD("Received: ");
    printLCD(u.recv);
    runMotor(u.recv);
    u.run = false;
    enableUART1();
}

//
// RX interrupt
//

void UART1receive() {
    unsigned long status;
    unsigned char uc_character[3];
    int i = 0;

    //
    // Get the interrrupt status.
    //

    status = UARTIntStatus(UART1_BASE, true);

    //
    // Clear the asserted interrupts.
    //

    UARTIntClear(UART1_BASE, status);

    //
    // Received characters
    //

    while (UARTCharsAvail(UART1_BASE)) {
        uc_character[i] = UARTCharGetNonBlocking(UART1_BASE);
        i++;
        uc_character[i] = '\0';
    }

    //
    // Set flag to run the motor
    //

    u.run = true;
    strcpy(u.recv, uc_character);
}

void UART1send(const unsigned char *string) {

    //
    // Loop while there are more characters to send.
    //

    while(string != 0x00) {
        UARTCharPutNonBlocking(UART1_BASE, *string++);
    }
}

void disableUART1() {
    IntDisable(INT_UART1);
    UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    UARTDisable(UART1_BASE);
}

void enableUART1() {
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    UARTEnable(UART1_BASE);
}

void initUART1() {

    //
    // Disable interrupts
    //

    disableUART1();

    //
    // Configure PB0 and PB1 as UART
    // 115200 baud, 8-N-1 operation
    //

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(UART1_PORT_BASE, UART_PINS);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    //
    // Enable interrupts and UART1
    //

    UARTIntRegister(UART1_BASE, UART1receive);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART1);
    UARTEnable(UART1_BASE);
}
