#ifndef LIB_LIBRARIES_H_
#define LIB_LIBRARIES_H_

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_nvic.h"
#include "inc/hw_ints.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/debug.h"
#include "driverlib/uart.h"
#include "driverlib/fpu.h"
#include "driverlib/timer.h"
#include "driverlib/udma.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"

typedef struct {
    unsigned char password[6];
} Solarco;

Solarco solar;

extern void delay_us(int);
extern void delay_ms(int);
extern void password();
extern void menu();
extern void motorControl();
extern void newPosition();
extern void rotateManually();
extern void changePW();
extern void lockDevice();
extern void companyInfo();
extern void teamRole();

#endif /* LIB_LIBRARIES_H_ */
