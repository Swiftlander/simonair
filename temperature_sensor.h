
byte pin_temperature = 25;   // GPIO pin where the DS18B20 is connected to  //25

// ==========
// SUHU
// ==========
OneWire oneWire(pin_temperature); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature temperatureSensor(&oneWire);
int value_temperature = 0;


void temperatureSensorFunction(){
   temperatureSensor.setResolution(10);
   temperatureSensor.requestTemperatures();
   value_temperature = temperatureSensor.getTempCByIndex(0);

}

void temperaturePrintToSerialMonitor(){
  Serial.println("============== SUHU ==============");
  Serial.print("Suhu: ");
  Serial.println(value_temperature);
  Serial.println();
}

