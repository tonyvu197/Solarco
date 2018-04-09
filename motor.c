#include "motor.h"

//
// Formula: Delay = 60 * F_CPU / 1 revolution steps / RPM
// Because SysCtlDelay() take 3 cycles to complete so F_CPU /= 3
//

void motorRPM(long double speed) {
    m.speed = 20 * SysCtlClockGet() / m.motorMaxStep / speed;
}

//
// Rotate motor
//

void stepMotor(int s) {
    switch (s) {
        case 0: // 01
            GPIOPinWrite(COILS_PORT_BASE, COILS, 4);
            break;
        case 1: // 11
            GPIOPinWrite(COILS_PORT_BASE, COILS, 12);
            break;
        case 2: // 10
            GPIOPinWrite(COILS_PORT_BASE, COILS, 8);
            break;
        case 3: // 00
            GPIOPinWrite(COILS_PORT_BASE, COILS, 0);
            break;
    }
}

//
// Run motor with 2 wires setup
//

void runMotor(unsigned char *step) {
    m.charStep = step;
    m.intStep = atoi(m.charStep);

    while (m.intStep > 0) {
        MAP_SysCtlDelay(m.speed);
        if (m.direction == 1) {
            m.stepNum++;
            if (m.stepNum == 1024) m.stepNum = 0;
        }
        else {
            if (m.stepNum == 0) m.stepNum = 1024;
            m.stepNum--;
        }
        m.intStep--;
        stepMotor(m.stepNum % 4);
    }
}

//
// Intialize output pin and set initial values
//

void initMotor() {
    GPIOPinTypeGPIOOutput(COILS_PORT_BASE, COILS);
    GPIOPinWrite(COILS_PORT_BASE, COILS, 0);
    m.direction = 1;        // Forward direction
    m.stepNum = 0;
    m.charStep = "0";
    m.intStep = 0;
    m.speed = 52083;        // 30 RPM
    m.charSpeed = "30";
    m.motorMaxStep = 1024;  // 1024 steps for 1 revolution
}
