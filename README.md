# ZMPT101B for RAK3172 (RUI3)

This repository is based on the original [ZMPT101B-arduino](https://github.com/Abdurraziq/ZMPT101B-arduino) library developed by Abdurraziq.  
The code has been **adapted to work properly with the RAK3172** using the **RUI3** framework, ensuring stable and accurate RMS readings with the module’s internal ADC.

---

## Main changes

### 1️⃣ Fixed-point sampling method  
- **Original:** RMS calculation was done using a time window with `micros()` based on mains frequency.  
- **Adaptation:** Implemented reading of a **fixed number of samples** (e.g., 1000 or 2000 points) at a constant sampling rate (~2 kHz).  
- **Reason:** The time-based method produced unstable readings due to jitter and phase misalignment. Using a fixed number of samples ensures that the average converges to the true RMS value even when starting at a random phase.

---

### 2️⃣ Automatic calibration function  
- **Addition:** Added `autoCalibrate(knownVoltage, samplesCount)` function, which measures a known real-world voltage and adjusts the `sensitivity` parameter accordingly.  
- **Reason:** The ZMPT101B gain varies depending on potentiometer adjustment and supply voltage. Automatic calibration guarantees accuracy without manual calculations.

---

## How the code works

1. **Fixed number of samples** is collected from the ADC, spaced by a constant delay (`SAMPLING_RATE`) to control the sampling rate.
2. Each sample is **centered** by subtracting `ADC_CENTER` (half of the ADC range).
3. The **RMS** value is calculated from the squared sum of samples.
4. The RMS in ADC steps is converted to volts at the sensor output using `VREF` and `ADC_SCALE`.
5. The result is multiplied by the **sensitivity** factor to get the actual mains voltage.

---

## Calibration process

The calibration is used to determine the **sensitivity** factor, which converts the RMS voltage measured at the ZMPT101B output into the actual mains voltage.

This factor is needed because:
- The ZMPT101B module contains a transformer and an op-amp stage with a potentiometer for gain adjustment.
- The output amplitude depends on this gain, the sensor's supply voltage, and hardware tolerances.
- Without calibration, the voltage readings will not match the real mains value.

---

## Adjustable parameters

- **`SAMPLES & CAL_SAMPLES `**  
  - Higher value → more stable readings, slower response.  
  - Lower value → faster readings, less stability.  

- **`SAMPLING_RATE` (in us)**  
  - Sets delay between samples → controls sampling rate.  
  - Example:  
    - 500 µs → 2 kHz sampling (good balance for 50/60 Hz)  
    - 250 µs → 4 kHz (higher resolution, more processing)  
    - 1000 µs → 1 kHz (lower resolution, faster loop)

- **`CAL_VOLTAGE`**  
  - Known RMS voltage (measured with a multimeter before test) 
  - Is used to calibrate the sensitivity parameter

- **`ADC_PIN`**  
  - Analog pin used 

- **`VREF` and `ADC_SCALE`**  
  - Adjust if using a different MCU/ADC reference voltage or resolution.
