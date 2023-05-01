#include "adc_lut_33.h"

byte pin_salinity = 33; // Pin Salinitas // 33

// ==========
// SALINITAS
// ==========
int raw_salinity_analogValue = 0;
double store_adc_value_salinity[SAMPLE_VALUE];
double sum_all_array_value_salinity = 0;
double adc_salinity;
double voltage_salinity;
double value_salinity = 0;

int ADC_READ_SALINITY(byte _pin_salinity){
    int _raw_salinity = analogRead(_pin_salinity);
    int _result_salinity = ADC_LUT_35[_raw_salinity];
    return _result_salinity;
}

void salinitySensor(){

    // for (int i = 0; i < SAMPLE_VALUE ; i++){
    //     raw_adc_salinity = ADC_READ_SALINITY(pin_salinity);
    //     store_adc_value_salinity[i] = raw_adc_salinity;
    // }

    // for (int i = 0; i < SAMPLE_VALUE; i++){
    //     sum_all_array_value_salinity += store_adc_value_salinity[i];
    // }

    // adc_salinity = sum_all_array_value_salinity / SAMPLE_VALUE;
    
    raw_salinity_analogValue = analogRead(pin_salinity); 
    adc_salinity = ADC_READ_SALINITY(pin_salinity);
    voltage_salinity = analogRead(pin_salinity) * (3.3 / 4095.0);

    
}

void salinityPrintToSerialMonitor(){
  Serial.println("============== SALINITY ==============");
  Serial.print("ADC salinity (Not Cal): ");
  Serial.println(raw_salinity_analogValue);
  Serial.print("ADC salinity (CAL): ");
  Serial.println(adc_salinity);
  Serial.print("Voltage salinity: ");
  Serial.println(voltage_salinity);
  Serial.print("Salinity Value: ");
  Serial.println(value_salinity);
        
}