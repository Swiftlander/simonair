#include "adc_lut_32.h"


// ==========
// SENSOR TDS
// ==========
byte pin_tds = 32; // Pin analog TDS
#define VREF 3.3      // analog reference voltage(Volt) of the ADC
#define SCOUNT  100           // sum of sample point

int raw_tds_analogValue = 0;

int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,raw_value_tds = 0,value_tds_cal = 0, temperature = 25;
double analogReadCal;


int value_temperature_dummy = 25;

double ADC_READ_TDS(byte _pin_tds)
{
  int _raw_tds = analogRead(_pin_tds);
  int _result_tds = ADC_LUT_32[_raw_tds];
  return _result_tds;
}

int getMedianNum(int bArray[], int iFilterLen)
{
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}


void tdsSensor()
{
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U) // every 40 milliseconds,read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    //  analogBuffer[analogBufferIndex] = analogRead(pin_tds);    //read the analog value and store into the buffer
    analogBuffer[analogBufferIndex] = ADC_READ_TDS(pin_tds); // read the analog value and store into the buffer
    analogReadCal = ADC_READ_TDS(pin_tds);
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT)
      analogBufferIndex = 0;
  }
  
  static unsigned long printTimepoint = millis();
  
  if (millis() - printTimepoint > 800U) {
      printTimepoint = millis();
      for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
        analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 4095.0;                                                                                                   // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      float compensationCoefficient = 1.0 + 0.02 * (value_temperature_dummy - 25.0);                                                                                                                // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationVoltage = averageVoltage / compensationCoefficient;                                                                                                             // temperature compensation
      raw_value_tds = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.67; // convert voltage value to tds value
    }        
}



void tdsPrintToSerialMonitor(){
  Serial.println("============== TDS ==============");
  Serial.print("ADC Value (Not Cal):");
  Serial.println(analogRead(pin_tds));
  Serial.print("ADC Value (Cal):");
  Serial.println(ADC_READ_TDS(pin_tds));
  Serial.print("TDS Value (RAW):");
  Serial.print(raw_value_tds);
  Serial.println("ppm");
  Serial.print("TDS Value (Cal):");
  Serial.print(value_tds_cal);
  Serial.println("ppm");
  Serial.println();
}
