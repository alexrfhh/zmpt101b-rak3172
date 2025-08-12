#ifndef ZMPT101B_h
#define ZMPT101B_h

#include <Arduino.h>

#define DEFAULT_SENSITIVITY 500.0f
#define ADC_SCALE 4095.0
#define VREF 3.3

#define ADC_CENTER ADC_SCALE/2
#define CONST VREF/ADC_SCALE

class ZMPT101B
{
public:
    ZMPT101B(uint8_t pin);
    void     setSensitivity(float value);
    float    getSensitivity();
    float    getRmsVoltage(uint16_t samplesCount = 1000);
    float    autoCalibrate(float knownVoltage, uint16_t samplesCount = 2000);

private:
    uint8_t  pin;
    float    sensitivity = DEFAULT_SENSITIVITY;
};

#endif
