
#include <DallasTemperature.h> // Library Sensor Suhu
#include <OneWire.h> // Library Sensor Suhu

// JUMLAH PENGAMBILAN SAMPEL
#define SAMPLE_VALUE 50

#include "tds_sensor.h"
#include "ph_sensor.h"
#include "tss_turbidity_sensor.h"
#include "mq_sensor.h"
#include "salinity_sensor.h"
#include "temperature_sensor.h"
#include "send_data.h"

#include "wifi_conf.h"

// ====================================================
// KONFIGURASI LED INTERNAL | START
// ====================================================
int indikator = LED_BUILTIN;
// ====================================================
// KONFIGURASI LED INTERNAL | END
// ====================================================

// INTERVAL PEMBACAAN
unsigned long intervalSendTime = 30000;
unsigned long prevCurrentTimeSend = 0;
unsigned long intervalPrintTime = 2000;
unsigned long prevCurrentTimePrint = 0;
unsigned long intervalSendDataTime = 15000;
unsigned long prevCurrentTimeSendData = 0;


void setup(){
    Serial.begin(115200);
    
    pinMode(pin_tds, INPUT);
    pinMode(pin_ph, INPUT);
    pinMode(pin_tss, INPUT);
    pinMode(pin_mq, INPUT);
    pinMode(pin_salinity, INPUT);
    temperatureSensor.begin();
}

void loop(){
    
  unsigned long currentTime = millis();


  temperatureSensorFunction();
  tdsSensor();
  tssTurbiditySensor();
  phSensor();
  salinitySensor();
  mqSensor();
    

    if(currentTime - prevCurrentTimePrint >= intervalPrintTime){
      
      temperaturePrintToSerialMonitor();
      phPrintToSerialMonitor();
      tssPrintToSerialMonitor();
      tdsPrintToSerialMonitor();
      mqPrintToSerialMonitor();
      salinityPrintToSerialMonitor();

      prevCurrentTimePrint = currentTime;
    }
  
  if(currentTime - prevCurrentTimeSendData >= intervalSendDataTime){
    initWiFi();
    sendData();
    WiFi.disconnect();
    prevCurrentTimeSendData = currentTime;
  }     
    
}
