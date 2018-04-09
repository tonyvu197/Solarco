#include "keypad.h"

const unsigned char *keymap[4][3] = {
                                     {"1","2","3"},
                                     {"4","5","6"},
                                     {"7","8","9"},
                                     {"*","0","#"}
};

void getKeypad(unsigned char *key) {
    k.isPressed = true;
    k.keyPressed = key;
}

void readKeypad() {

    //
    // Disable interrupt
    //

    GPIOIntDisable(ROW_PORT_BASE, KEYPAD_ROWS);
    GPIOIntClear(ROW_PORT_BASE, KEYPAD_ROWS);

    //
    // Detect keypad's row and column
    //

    if (GPIOPinRead(ROW_PORT_BASE, KEYPAD_ROW_1) == 0) {
        k.row = 0;

        GPIOPinTypeGPIOOutput(ROW_PORT_BASE, KEYPAD_ROWS);
        GPIOPinWrite(ROW_PORT_BASE, KEYPAD_ROWS, 0);
        GPIOPinTypeGPIOInput(COL_PORT_BASE, KEYPAD_COLS);
        GPIOPadConfigSet(COL_PORT_BASE, KEYPAD_COLS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

        if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_1) == 0) { k.col = 0; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_2) == 0) { k.col = 1; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_3) == 0) { k.col = 2; }

        delay_ms(1);
        getKeypad(keymap[k.row][k.col]);
    }
    else if (GPIOPinRead(ROW_PORT_BASE, KEYPAD_ROW_2) == 0) {
        k.row = 1;

        GPIOPinTypeGPIOOutput(ROW_PORT_BASE, KEYPAD_ROWS);
        GPIOPinWrite(ROW_PORT_BASE, KEYPAD_ROWS, 0);
        GPIOPinTypeGPIOInput(COL_PORT_BASE, KEYPAD_COLS);
        GPIOPadConfigSet(COL_PORT_BASE, KEYPAD_COLS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

        if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_1) == 0) { k.col = 0; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_2) == 0) { k.col = 1; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_3) == 0) { k.col = 2; }

        delay_ms(1);
        getKeypad(keymap[k.row][k.col]);

    }
    else if (GPIOPinRead(ROW_PORT_BASE, KEYPAD_ROW_3) == 0) {
        k.row = 2;

        GPIOPinTypeGPIOOutput(ROW_PORT_BASE, KEYPAD_ROWS);
        GPIOPinWrite(ROW_PORT_BASE, KEYPAD_ROWS, 0);
        GPIOPinTypeGPIOInput(COL_PORT_BASE, KEYPAD_COLS);
        GPIOPadConfigSet(COL_PORT_BASE, KEYPAD_COLS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

        if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_1) == 0) { k.col = 0; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_2) == 0) { k.col = 1; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_3) == 0) { k.col = 2; }

        delay_ms(1);
        getKeypad(keymap[k.row][k.col]);
    }
    else if (GPIOPinRead(ROW_PORT_BASE, KEYPAD_ROW_4) == 0) {
        k.row = 3;

        GPIOPinTypeGPIOOutput(ROW_PORT_BASE, KEYPAD_ROWS);
        GPIOPinWrite(ROW_PORT_BASE, KEYPAD_ROWS, 0);
        GPIOPinTypeGPIOInput(COL_PORT_BASE, KEYPAD_COLS);
        GPIOPadConfigSet(COL_PORT_BASE, KEYPAD_COLS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

        if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_1) == 0) { k.col = 0; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_2) == 0) { k.col = 1; }
        else if (GPIOPinRead(COL_PORT_BASE, KEYPAD_COL_3) == 0) { k.col = 2; }

        delay_ms(1);
        getKeypad(keymap[k.row][k.col]);
    }

    //
    // Reset to normal
    //

    GPIOPinTypeGPIOOutput(COL_PORT_BASE, KEYPAD_COLS);
    GPIOPinWrite(COL_PORT_BASE, KEYPAD_COLS, 0);
    GPIOPinTypeGPIOInput(ROW_PORT_BASE, KEYPAD_ROWS);
    GPIOPadConfigSet(ROW_PORT_BASE, KEYPAD_ROWS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //GPIOIntRegister(ROW_PORT_BASE, readKeypad);
    //GPIOIntTypeSet(ROW_PORT_BASE, KEYPAD_ROWS, GPIO_FALLING_EDGE);
    GPIOIntEnable(ROW_PORT_BASE, KEYPAD_ROWS);
}

void initKeypad() {

    //
    // Set column as output
    //

    GPIOPinTypeGPIOOutput(COL_PORT_BASE, KEYPAD_COLS);
    GPIOPinWrite(COL_PORT_BASE, KEYPAD_COLS, 0);

    //
    // Set row as input and pull-up
    //

    GPIOPinTypeGPIOInput(ROW_PORT_BASE, KEYPAD_ROWS);
    GPIOPadConfigSet(ROW_PORT_BASE, KEYPAD_ROWS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //
    // Interrupt setup
    //

    GPIOIntDisable(ROW_PORT_BASE, KEYPAD_ROWS);
    GPIOIntClear(ROW_PORT_BASE, KEYPAD_ROWS);
    GPIOIntRegister(ROW_PORT_BASE, readKeypad);
    GPIOIntTypeSet(ROW_PORT_BASE, KEYPAD_ROWS, GPIO_FALLING_EDGE);
    GPIOIntEnable(ROW_PORT_BASE, KEYPAD_ROWS);
}
