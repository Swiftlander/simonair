// ====================================================
// WIFI
// ====================================================
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Galaxy M33 5GD3C6";
const char* password = "bifo2473";

IPAddress local_IP(192, 168, 133, 171);
IPAddress gateway(192, 168, 133, 14);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
