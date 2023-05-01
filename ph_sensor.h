#include "adc_lut_35.h"

byte pin_ph = 35; // Pin analog ph // 35

// ==========
// SENSOR PH
// ==========

int raw_ph_analogValue = 0;

float calibrationValue_ph = 26.34;

double raw_adc_ph;
double store_adc_value_ph[SAMPLE_VALUE];
double sum_all_array_value_ph = 0;
double adc_ph;
double voltage_ph;
double PH_step;
double value_ph;

// kalibrasi Ph
float PH4 = 3.09f;
float PH7 = 2.6f;



int ADC_READ_PH(byte _pin_ph){
    int _raw_ph = analogRead(_pin_ph);
    int _result_ph = ADC_LUT_35[_raw_ph];
    return _result_ph;
}

void phSensor(){
    raw_ph_analogValue = analogRead(pin_ph);
    raw_adc_ph = ADC_READ_PH(pin_ph);
    voltage_ph = raw_adc_ph * (3.3 / 4095.0);

    value_ph = -5.70 * voltage_ph + calibrationValue_ph;
    PH_step = (PH4 - PH7) / 3;
    value_ph = (7.00f + ((PH7 - voltage_ph) / PH_step)) + 0.9f;
}

void phPrintToSerialMonitor(){
  Serial.println("============== PH ==============");
  Serial.print("ADC PH (Not Cal): ");
  Serial.println(raw_ph_analogValue);
  Serial.print("ADC PH (Cal): ");
  Serial.println(raw_adc_ph);
  Serial.print("Voltage PH: ");
  Serial.println(voltage_ph);
  Serial.print("Nilai PH: ");
  Serial.println(value_ph);
}
