#include "sensor.h"

void readSensor() {

    uint32_t ulValue[1];

    //
    // Trigger the ADC conversion.
    //

    ADCProcessorTrigger(SENSOR_BASE, 3);

    //
    // Wait for conversion to be completed.
    //

    while(!ADCIntStatus(SENSOR_BASE, 3, false));

    //
    // Clear the ADC interrupt flag.
    //

    ADCIntClear(SENSOR_BASE, 3);

    //
    // Read ADC Value.
    //

    ADCSequenceDataGet(SENSOR_BASE, 3, ulValue);

    if (ulValue[0] < 512) {
        printCharLCD(0xFF);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
    }
    else if (ulValue[0] >= 512 && ulValue[0] < 1024 ) {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
    }
    else if (ulValue[0] >= 1024 && ulValue[0] < 1536 ) {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
    }
    else if (ulValue[0] >= 1536 && ulValue[0] < 2048 ) {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
    }
    else if (ulValue[0] >= 2048 && ulValue[0] < 2560 ) {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(7);
        printCharLCD(7);
        printCharLCD(7);
    }
    else if (ulValue[0] >= 2560 && ulValue[0] < 3072 ) {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(7);
        printCharLCD(7);
    }
    else if (ulValue[0] >= 3072 && ulValue[0] < 3584 ) {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(7);
    }
    else {
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
        printCharLCD(0xFF);
    }
}


void initSensor() {

    //
    // Select the analog ADC function for these pins.
    // Consult the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    //GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3);

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    //ADCSequenceDisable(ADC0_BASE, 0);

    ADCSequenceConfigure(SENSOR_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    //
    // Configure step 0 to 7 on sequence 0.  Sample the temperature sensor
    // (ADC_CTL_TS) and configure the interrupt flag (ADC_CTL_IE) to be set
    // when the sample is done.  Tell the ADC logic that this is the last
    // conversion on sequence 0 (ADC_CTL_END).  Sequence 3 has only one
    // programmable step.  Sequence 1 and 2 have 4 steps, and sequence 0 has
    // 8 programmable steps. For more information on the
    // ADC sequences and steps, reference the datasheet.
    //

    /*ADCSequenceStepConfigure(SENSOR_BASE, 0, 0, ADC_CTL_TS);
    ADCSequenceStepConfigure(SENSOR_BASE, 0, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(SENSOR_BASE, 0, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(SENSOR_BASE, 0, 3, ADC_CTL_TS);
    ADCSequenceStepConfigure(SENSOR_BASE, 0, 4, ADC_CTL_TS);
    ADCSequenceStepConfigure(SENSOR_BASE, 0, 5, ADC_CTL_TS);
    ADCSequenceStepConfigure(SENSOR_BASE, 0, 6, ADC_CTL_TS);*/
    ADCSequenceStepConfigure(SENSOR_BASE, 3, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);

    //
    // Since sample sequence 0 is now configured, it must be enabled.
    //

    ADCSequenceEnable(SENSOR_BASE, 3);

    //
    // Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample.
    //

    ADCIntClear(SENSOR_BASE, 3);
}
