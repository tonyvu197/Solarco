#ifndef LIB_SENSOR_H_
#define LIB_SENSOR_H_

#include "libraries.h"

#define SENSOR_BASE ADC0_BASE
#define SENSOR_PERIPH SYSCTL_PERIPH_ADC0

typedef struct {
    unsigned char *sensorValue;
} Sensor;

Sensor s;

void initSensor();
//void readSensor();

#endif /* LIB_SENSOR_H_ */
