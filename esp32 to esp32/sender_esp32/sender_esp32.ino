#include <WiFi.h>
#include <esp_now.h>

// Receiver's MAC Address
uint8_t receiverMAC[] = { 0x30, 0xAE, 0xA4, 0xEB, 0x24, 0x1C };  // Replace with the actual MAC address of the receiver

// Message structure
typedef struct {
  int num;
  char text[32];
} Message;

Message msg;

// checking the status
void onSend(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Message Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(9600);

//checking MAC address of 
  WiFi.mode(WIFI_STA);
  Serial.print("ESP32 MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register send callback
  esp_now_register_send_cb(onSend);

  // Add peer (receiver)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Prepare message
  msg.num = 6969;
  strcpy(msg.text, "number to send");
}

void loop() {
  // Send message
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&msg, sizeof(msg));
  if (result == ESP_OK) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending message");
  }
  delay(2000); 
}
