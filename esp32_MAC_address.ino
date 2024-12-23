#include <WiFi.h>

void setup() {
  Serial.begin(9600);
}
void loop() {

  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
  delay(1000);
}
