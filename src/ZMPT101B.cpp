#include "ZMPT101B.h"

#define SAMPLING_RATE 500 // interval in ms between each measure

ZMPT101B::ZMPT101B(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

void ZMPT101B::setSensitivity(float value) {
    sensitivity = value;
}

float ZMPT101B::getSensitivity() {
    return sensitivity;
}

float ZMPT101B::getRmsVoltage(uint16_t samplesCount) {
    uint64_t sumSq = 0;
    for (uint16_t i = 0; i < samplesCount; i++) {
        int raw = analogRead(pin);
        int32_t d = raw - (int)ADC_CENTER; 
        sumSq += (uint64_t)d * (uint64_t)d;
        delayMicroseconds(SAMPLING_RATE); 
    }
    float rmsSteps = sqrt((float)sumSq / (float)samplesCount);
    float vSensorRms = rmsSteps * CONST;
    return vSensorRms * sensitivity;
}

float ZMPT101B::autoCalibrate(float knownVoltage, uint16_t samplesCount) {
    uint64_t sumSq = 0;
    for (uint16_t i = 0; i < samplesCount; i++) {
        int raw = analogRead(pin);
        int32_t d = raw - (int)ADC_CENTER;
        sumSq += (uint64_t)d * (uint64_t)d;
        delayMicroseconds(SAMPLING_RATE); 
    }
    float rmsSteps = sqrt((float)sumSq / (float)samplesCount);
    float vSensorRms = rmsSteps * CONST;
    sensitivity = knownVoltage / vSensorRms;
    return sensitivity;
}
