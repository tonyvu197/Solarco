/********************
 * Author: Tony Vu
 *
 * LCD Connection:
 * PE1 -> RS
 * PE2 -> EN
 * PD0 -> D4
 * PD1 -> D5
 * PD2 -> D6
 * PD3 -> D7

 * Keypad Connection:
 * PC4 -> ROW 1
 * PC5 -> ROW 2
 * PC6 -> ROW 3
 * PC7 -> ROW 4
 * PA2 -> COL 1
 * PA3 -> COL 2
 * PA4 -> COL 3

 * Bluetooth Connection:
 * PB0 -> RX
 * PB1 -> TX
 * PB4 -> EN
 * PB5 -> ST

 * Motor Connection:
 * PF2 -> Coil A
 * PF3 -> Coil B

 * Light Sensor Connection:
 * PE3 -> Sensor Ouput
********************/

#include "display.h"
#include "keypad.h"
#include "motor.h"
#include "sensor.h"
#include "UART.h"

void delay_us(int n) {
    MAP_SysCtlDelay((SysCtlClockGet() / 3000000) * n);
}

void delay_ms(int n) {
    MAP_SysCtlDelay((SysCtlClockGet() / 3000) * n);
}

void password() {
    k.isPressed = false;
    clearLCD();
    bool unlock = false;

    while (!unlock) {
        unsigned char pass[6] = {'\0'};
        setCursorPositionLCD(5, 1);
        printLCD("Enter PIN:");
        setCursorPositionLCD(7, 2);
        GPIOIntEnable(ROW_PORT_BASE, KEYPAD_ROWS);

        while (strlen(pass) < 6) {
            if (k.isPressed) {
                strcat(pass, k.keyPressed);
                printLCD("*");
                k.isPressed = false;
            }
        }

        if (strcmp(solar.password, pass) != 0) {
            GPIOIntDisable(ROW_PORT_BASE, KEYPAD_ROWS); // Prevent keypad spamming
            setCursorPositionLCD(4, 3);
            printLCD("Wrong PIN!!!");
            delay_ms(1000);
            clearLCD();
        }
        else unlock = true;
    }
}

void menu() {
    k.isPressed = false;
    clearLCD();

    setCursorPositionLCD(0, 0);
    printLCD("1. Motor Control");
    setCursorPositionLCD(0, 1);
    printLCD("2. Change P/W");
    setCursorPositionLCD(0, 2);
    printLCD("3. Lock Device");
    setCursorPositionLCD(0, 3);
    printLCD("4. About");

    while (1) {
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "1") == 0) motorControl();
            else if (strcmp(k.keyPressed, "2") == 0) changePW();
            else if (strcmp(k.keyPressed, "3") == 0) lockDevice();
            else if (strcmp(k.keyPressed, "4") == 0) companyInfo();
            else k.isPressed = false;
        }
    }
}

void motorControl() {
    k.isPressed = false;
    clearLCD();

    setCursorPositionLCD(0, 0);
    printLCD("1. New Position");
    setCursorPositionLCD(0, 1);
    printLCD("2. Rotate Manually");
    setCursorPositionLCD(0, 2);
    printLCD("3. Change RPM");
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");

    while (1) {
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "1") == 0) newPosition();
            else if (strcmp(k.keyPressed, "2") == 0) rotateManually();
            else if (strcmp(k.keyPressed, "3") == 0) changeRPM();
            else if (strcmp(k.keyPressed, "*") == 0) menu();
            else k.isPressed = false;
        }
    }
}

void newPosition() {
    k.isPressed = false;
    clearLCD();

    unsigned char angle[3] = {'\0'};
    int i = 0;

    setCursorPositionLCD(0, 0);
    printCharLCD(6);
    printLCD("Intensity: ");
    //printLCD(Light Sensor Here);
    setCursorPositionLCD(0, 1);
    printLCD("Angle to move: ");
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");
    setCursorPositionLCD(17, 3);
    printLCD("#");
    printCharLCD(0);
    printCharLCD(3);

    while (1) {
        setCursorPositionLCD(12, 0);
        readSensor();
        setCursorPositionLCD(15 + i, 1);
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "#") == 0) { runMotor(angle); newPosition(); }
            else if (strcmp(k.keyPressed, "*") == 0) motorControl();
            else {
                strcat(angle, k.keyPressed);
                printLCD(k.keyPressed);
                i++;
                k.isPressed = false;
            }
        }
    }
}

void rotateManually() {
    k.isPressed = false;
    clearLCD();

    setCursorPositionLCD(0, 0);
    printCharLCD(6);
    printLCD("Intensity: ");
    setCursorPositionLCD(0, 1);
    printCharLCD(0);
    printLCD("4");
    setCursorPositionLCD(18, 1);
    printLCD("6");
    printCharLCD(1);
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");

    while (1) {
        setCursorPositionLCD(12, 0);
        readSensor();
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "6") == 0) {
                m.direction = 1;
                runMotor("10");
                rotateManually();
            }
            else if (strcmp(k.keyPressed, "4") == 0) {
                m.direction = 0;
                runMotor("10");
                rotateManually();
            }
            else if (strcmp(k.keyPressed, "*") == 0) motorControl();
            else k.isPressed = false;
        }
    }
}

void changeRPM() {
    k.isPressed = false;
    clearLCD();
    unsigned char charSpeed[3] = {'\0'};
    long double intSpeed;

    setCursorPositionLCD(0, 0);
    printLCD("Set RPM: ");
    setCursorPositionLCD(0, 1);
    printLCD("Current RPM: ");
    printLCD(m.charSpeed);
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");
    setCursorPositionLCD(17, 3);
    printLCD("#");
    printCharLCD(2);
    printCharLCD(1);
    setCursorPositionLCD(9, 0);

    while (1) {
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "#") == 0) {
                m.charSpeed = charSpeed;
                intSpeed = strtold(charSpeed, NULL);
                motorRPM(intSpeed);
                changeRPM();
            }
            else if (strcmp(k.keyPressed, "*") == 0) motorControl();
            else {
                strcat(charSpeed, k.keyPressed);
                printLCD(k.keyPressed);
                k.isPressed = false;
            }
        }
    }
}

void changePW() {
    password();
    k.isPressed = false;
    clearLCD();

    unsigned char pass[6] = {'\0'};
    setCursorPositionLCD(3, 0);
    printLCD("Enter New PIN:");
    setCursorPositionLCD(7, 1);

    while (strlen(pass) < 6) {
        if (k.isPressed) {
            strcat(pass, k.keyPressed);
            printLCD(k.keyPressed);
            k.isPressed = false;
        }
    }

    setCursorPositionLCD(6, 2);
    printLCD("Confirm?");
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");
    setCursorPositionLCD(17, 3);
    printLCD("#");
    printCharLCD(0);
    printCharLCD(3);

    while (1) {
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "#") == 0) {
                strcpy(solar.password, pass);
                menu();
            }
            else if (strcmp(k.keyPressed, "*") == 0) menu();
            else k.isPressed = false;
        }
    }
}

void lockDevice() {
    k.isPressed = false;
    clearLCD();

    password();
    menu();
}

void companyInfo() {
    k.isPressed = false;
    clearLCD();

    setCursorPositionLCD(4, 0);
    printLCD("Solarco Inc.");
    setCursorPositionLCD(2, 1);
    printLCD("Once gone diode,");
    setCursorPositionLCD(2, 2);
    printLCD("never go bananas");
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");
    setCursorPositionLCD(8, 3);
    printCharLCD(4);
    printCharLCD(5);
    printCharLCD(4);
    printCharLCD(5);
    setCursorPositionLCD(17, 3);
    printLCD("#");
    printCharLCD(2);
    printCharLCD(1);

    while (1) {
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "*") == 0) menu();
            else if (strcmp(k.keyPressed, "#") == 0) teamRole();
            else k.isPressed = false;
        }
    }

}

void teamRole() {
    k.isPressed = false;
    clearLCD();

    setCursorPositionLCD(0, 0);
    printLCD("Software Div.: Tony");
    setCursorPositionLCD(0, 1);
    printLCD("Hardware Div.: Tyler");
    setCursorPositionLCD(0, 2);
    printLCD("Marketing Div.: Ajay");
    setCursorPositionLCD(0, 3);
    printCharLCD(0);
    printCharLCD(2);
    printLCD("*");

    while (1) {
        if (k.isPressed) {
            if (strcmp(k.keyPressed, "*") == 0) companyInfo();
            else k.isPressed = false;
        }
    }
}


void main() {

    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //

    FPUEnable();
    FPULazyStackingEnable();

    //
    // 80MHz System Clock Frequency, 16MHz crystal clock
    //

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //
    // Enable ports
    //

    SysCtlPeripheralEnable(KEYPAD_ROW_PERIPH);
    while(!SysCtlPeripheralReady(KEYPAD_ROW_PERIPH));
    SysCtlPeripheralEnable(KEYPAD_COL_PERIPH);
    while(!SysCtlPeripheralReady(KEYPAD_COL_PERIPH));
    SysCtlPeripheralEnable(LCD_DATA_PERIPH);
    while(!SysCtlPeripheralReady(LCD_DATA_PERIPH));
    SysCtlPeripheralEnable(LCD_CMD_PERIPH);
    while(!SysCtlPeripheralReady(LCD_CMD_PERIPH));
    SysCtlPeripheralEnable(MOTOR_PERIPH);
    while(!SysCtlPeripheralReady(MOTOR_PERIPH));
    SysCtlPeripheralEnable(UART1_PORT_PERIPH);
    while(!SysCtlPeripheralReady(UART1_PORT_PERIPH));
    SysCtlPeripheralEnable(UART1_PERIPH);
    SysCtlPeripheralEnable(SENSOR_PERIPH);

    //
    // Initialize devices
    //

    initLCD();
    initKeypad();
    initMotor();
    initSensor();
    initUART1();

    //
    // Enable processor interrupts
    //

    IntMasterEnable();


    //
    // Initial password
    //

    strcpy(solar.password, "123456");

    //
    // Fun Time
    //

    clearLCD();
    password();
    menu();
}
