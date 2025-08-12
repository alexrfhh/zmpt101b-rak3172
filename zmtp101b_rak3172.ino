#include "src/ZMPT101B.h"

#define ADC_PIN WB_IO4 // A2 
#define SAMPLES 2000 // range 1000 ~ 4000
#define CAL_SAMPLES 2000
#define CAL_VOLTAGE 127.0   // input voltage to calibrate the sens parameter 

ZMPT101B voltageSensor(ADC_PIN);

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);

    float sens = voltageSensor.autoCalibrate(CAL_VOLTAGE, CAL_SAMPLES);
    Serial.print("Sensitivity: ");
    Serial.println(sens);
}

void loop() {
    float voltage = voltageSensor.getRmsVoltage(SAMPLES); 
    Serial.println(voltage, 2);
    delay(1000);
}
