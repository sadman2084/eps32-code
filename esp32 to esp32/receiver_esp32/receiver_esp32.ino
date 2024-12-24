#include <WiFi.h>
#include <esp_now.h>

typedef struct {
  int num;
  char text[32];
} Message;

Message msg;

void onReceive(const esp_now_recv_info *info, const uint8_t *data, int len) {
  memcpy(&msg, data, sizeof(msg));

  Serial.print("Message received from: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  Serial.print("Message: ");
  Serial.println(msg.text);

    Serial.print("number: ");
  Serial.println(msg.num);
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  Serial.print("ESP32 MAC Address: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}

void loop() {
}
