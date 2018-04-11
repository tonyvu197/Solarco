#include "bluetooth.h"

#define TX_BUFFER_EMPTY (b.txReadIndex == b.txWriteIndex)
#define TX_BUFFER_FULL (((b.txWriteIndex + 1) % b.txBufferSize) == b.txReadIndex)
#define RX_BUFFER_EMPTY (b.rxReadIndex == b.rxWriteIndex)
#define RX_BUFFER_FULL (((b.rxWriteIndex + 1) % b.rxBufferSize) == b.rxReadIndex)

/*
void setupBluetooth() {

}

void sendBluetooth(unsigned char *string) {
    while (*string) {
        UARTCharPutNonBlocking(UART1_BASE, *string++);
    }
}
*/

void receiveBluetooth() {
    /*
    b.isReceived = UARTCharsAvail(UART1_BASE);

    if (b.isReceived) {
        b.received = UARTCharGet(UART0_BASE);
        runMotor("16");
    }
    */

    unsigned long ulInts;
    long lChar;

    //
    // Get and clear the current interrupt source(s)
    //

    ulInts = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ulInts);

    //
    // Are we being interrupted because the TX FIFO has space available?
    //

    if (ulInts & UART_INT_TX) {

        //
        // Move as many bytes as we can into the transmit FIFO.
        //

        primeTransmit(UART1_BASE);

        //
        // If the output buffer is empty, turn off the transmit interrupt.
        //

        if (TX_BUFFER_EMPTY) UARTIntDisable(UART1_BASE, UART_INT_TX);
    }
    if (ulInts & (UART_INT_RX | UART_INT_RT)) {
        while(UARTCharsAvail(UART1_BASE)) {

            //
            // Read a character
            //

            lChar = UARTCharGetNonBlocking(UART1_BASE);

            //
            // If there is space in the receive buffer, put the character
            // there, otherwise throw it away.
            //

            uint8_t volatile full = RX_BUFFER_FULL;
            if(full) break;

           b.rxBuffer[b.rxWriteIndex] = (unsigned char)(lChar & 0xFF);
           b.rxWriteIndex = ((b.rxWriteIndex) + 1) % b.rxBufferSize;

            //
            // If we wrote anything to the transmit buffer, make sure it actually
            // gets transmitted.
            //
        }
        primeTransmit(UART1_BASE);
        UARTIntEnable(UART1_BASE, UART_INT_TX);
    }

    runMotor(b.rxBuffer);
}

void flushAll() {
    // Wait for transmission of outgoing data
    while(!TX_BUFFER_EMPTY);

    while (UARTBusy(UART1_BASE));

    b.txReadIndex = 0;
    b.txWriteIndex = 0;

    //
    // Flush the receive buffer.
    //

    b.rxReadIndex = 0;
    b.rxWriteIndex = 0;
}

void primeTransmit(unsigned long ulBase) {

    //
    // Do we have any data to transmit?
    //

    if (!TX_BUFFER_EMPTY) {

        //
        // Disable the UART interrupt. If we don't do this there is a race
        // condition which can cause the read index to be corrupted.
        //

        IntDisable(INT_UART1);

        //
        // Yes - take some characters out of the transmit buffer and feed
        // them to the UART transmit FIFO.
        //

        while (!TX_BUFFER_EMPTY) {
            while (UARTSpaceAvail(ulBase) && !TX_BUFFER_EMPTY) {
                UARTCharPutNonBlocking(ulBase, b.txBuffer[b.txReadIndex]);
                b.txReadIndex = (b.txReadIndex + 1) % b.txBufferSize;
            }
        }

        //
        // Re-enable the UART interrupt.
        //

        IntEnable(INT_UART1);
    }
}

void setBufferSize(unsigned long txsize, unsigned long rxsize) {
    if (txsize > 0)
        b.txBufferSize = txsize;
    if (rxsize > 0)
        b.rxBufferSize = rxsize;
}

void end() {
    unsigned long ulInt = IntMasterDisable();

    flushAll();

    //
    // If interrupts were enabled when we turned them off, turn them
    // back on again.
    //

    if(!ulInt) IntMasterEnable();

    IntDisable(INT_UART1);
    UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT);
}

int available() {
    return((b.rxWriteIndex >= b.rxReadIndex) ? (b.rxWriteIndex - b.rxReadIndex) : b.rxBufferSize - (b.rxReadIndex - b.rxWriteIndex));
}

int peek() {
    unsigned char cChar = 0;

    //
    // Wait for a character to be received.
    //

    if(RX_BUFFER_EMPTY)
    {
        return -1;
        //
        // Block waiting for a character to be received (if the buffer is
        // currently empty).
        //
    }

    //
    // Read a character from the buffer.
    //
    cChar = b.rxBuffer[b.rxReadIndex];
    //
    // Return the character to the caller.
    //
    return(cChar);
}

int read() {
    if(RX_BUFFER_EMPTY) {
        return -1;
    }

    //
    // Read a character from the buffer.
    //

    unsigned char cChar = b.rxBuffer[b.rxReadIndex];
    b.rxReadIndex = ((b.rxReadIndex) + 1) % b.rxBufferSize;
    return cChar;
}

void flush() {
    while(!TX_BUFFER_EMPTY);
    while (UARTBusy(UART1_BASE)) ;
}

size_t write(uint8_t c) {

    unsigned int numTransmit = 0;

    //
    // Check for valid arguments.
    //

    ASSERT(c != 0);

    //
    // Send the character to the UART output.
    //

    while (TX_BUFFER_FULL);
    b.txBuffer[b.txWriteIndex] = c;
    b.txWriteIndex = (b.txWriteIndex + 1) % b.txBufferSize;
    numTransmit ++;

    //
    // If we have anything in the buffer, make sure that the UART is set
    // up to transmit it.
    //

    if(!TX_BUFFER_EMPTY)
    {
        primeTransmit(UART1_BASE);
        UARTIntEnable(UART1_BASE, UART_INT_TX);
    }

    //
    // Return the number of characters written.
    //
    return(numTransmit);
}

void initBluetooth() {

    //
    // Constructors
    //

    b.txWriteIndex = 0;
    b.txReadIndex = 0;
    b.rxWriteIndex = 0;
    b.rxReadIndex = 0;
    b.txBuffer = (unsigned char *) 0xFFFFFFFF;
    b.rxBuffer = (unsigned char *) 0xFFFFFFFF;
    b.txBufferSize = SERIAL_BUFFER_SIZE;
    b.rxBufferSize = SERIAL_BUFFER_SIZE;

    //
    // Configure PB0 and PB1 as UART
    // 115200 baud, 8-N-1 operation
    //

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(BLT_PORT_BASE, UART_PINS);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    //
    // Set the UART to interrupt whenever the TX FIFO is almost empty or
    // when any character is received.
    //
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    flushAll();
    UARTIntDisable(UART1_BASE, 0xFFFFFFFF);

    //
    // Allocate TX & RX buffers
    // Make sure buffers are ready before interrupts are enabled
    // so the handlers do not fail because of unitialized pointers
    //

    // Catch attempts to re-init this Serial instance by freeing old buffer first
    if (b.txBuffer != (unsigned char *)0xFFFFFFFF) free(b.txBuffer);
    // Catch attempts to re-init this Serial instance by freeing old buffer first
    if (b.rxBuffer != (unsigned char *)0xFFFFFFFF) free(b.rxBuffer);

    b.txBuffer = (unsigned char *) malloc(b.txBufferSize);
    b.rxBuffer = (unsigned char *) malloc(b.rxBufferSize);

    //
    // Enable interrupts
    //

    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART1);

    //
    // Enable the UART operation.
    //

    UARTEnable(UART1_BASE);
}
