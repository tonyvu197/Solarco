#ifndef LIB_LIBRARIES_H_
#define LIB_LIBRARIES_H_

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_nvic.h"
#include "inc/hw_ints.h"
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

#endif /* LIB_LIBRARIES_H_ */
