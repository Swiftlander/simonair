#include "adc_lut_34.h"

byte pin_tss = 34; // Pin analog tss/TURBIDITY

// ==========
// TSS/TURBIDITY
// ==========
int raw_tssTurbidity_analogValue = 0;
double raw_adc_tss;
double store_adc_value_tss[SAMPLE_VALUE];
double sum_all_array_value_tss = 0;
double adc_tss;
double voltage_tss;
double value_tss = 0;


int ADC_READ_TSS(byte _pin_tss){
    int _raw_tss = analogRead(_pin_tss);
    int _result_tss = ADC_LUT_35[_raw_tss];
    return _result_tss;
}


void tssTurbiditySensor(){
  raw_tssTurbidity_analogValue = analogRead(pin_tss); 
  raw_adc_tss = ADC_READ_TSS(pin_tss);
  voltage_tss = raw_adc_tss * (3.3 / 4095.0);
    
}


void tssPrintToSerialMonitor(){
  Serial.println("============== TSS ==============");
  Serial.print("ADC TSS (Not Cal): ");
  Serial.println(raw_tssTurbidity_analogValue);
  Serial.print("ADC TSS (Cal): ");
  Serial.println(raw_adc_tss);
  Serial.print("Voltage TSS: ");
  Serial.println(voltage_tss);
  Serial.print("Value TSS: ");
  Serial.println(value_tss);
  Serial.println();
}
