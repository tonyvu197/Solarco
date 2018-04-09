#ifndef LIB_MOTOR_H_
#define LIB_MOTOR_H_

#include "libraries.h"

#define COIL_1 GPIO_PIN_2
#define COIL_2 GPIO_PIN_3
#define COILS COIL_1 | COIL_2

#define COILS_PORT_BASE GPIO_PORTF_BASE // Control pins connect to port F
#define MOTOR_PERIPH SYSCTL_PERIPH_GPIOF

typedef struct {
    int direction;              // 1 forward, 0 backward
    long double speed;          // Rotate speed of the motor
    unsigned char *charSpeed;
    long double motorMaxStep;   // Max steps for 1 revolution of the motor
    unsigned char *charStep;    // Number of steps the motor will run
    int intStep;                // Number of steps in integer
    int stepNum;                // Current step number
} Motor;

Motor m;

void motorRPM(long double);
void stepMotor(int);
void runMotor(unsigned char *);
void initMotor();

#endif /* LIB_MOTOR_H_ */
