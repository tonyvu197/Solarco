#ifndef LIB_SENSOR_H_
#define LIB_SENSOR_H_

#include "libraries.h"

#define SENSOR_BASE ADC0_BASE
#define SENSOR_PERIPH SYSCTL_PERIPH_ADC0

extern void initSensor();
extern void readSensor();

#endif /* LIB_SENSOR_H_ */
