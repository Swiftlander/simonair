#include <HTTPClient.h>  //Board = Version 2.7.4
#include <ArduinoJson.h> //Library = arduinoJson 6.15.1

const char *nama = "Aquarium_1";

byte server[] = {103, 179, 57, 67};
WiFiClient client;
const int httpPort = 80;
String url;
unsigned long timeout;

void sendData(){

    float suhu = value_ph;
    float ph = value_temperature;
    float amonia = value_mq_ppm;
    float tss = value_tss;
    float tds = raw_value_tds;
    float salinitas = value_salinity;
    // Serial.println(suhu);
    // Serial.println(ph);
    // Serial.println(amonia);
    // Serial.println(tss);
    // Serial.println(tds);
    // Serial.println(salinitas);

    Serial.print("connecting to ");
    // Serial.println(server);

    if (!client.connect(server, httpPort))
    {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    url = "/monitoring/getValue/";
    url += nama;
    url += "/";
    url += suhu;
    url += "/";
    url += ph;
    url += "/";
    url += amonia;
    url += "/";
    url += tss;
    url += "/";
    url += tds;
    url += "/";
    url += salinitas;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: ikan.portalsvipb.com\r\n" +
                 "Connection: close\r\n\r\n");
    timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
    Serial.println();

}
