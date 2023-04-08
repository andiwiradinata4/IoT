
#include <WiFi.h>

const char* ssid = "Jojo";
const char* password = "MauTauAja";

// Configure IP Address of the local access point
IPAddress localIP(192, 168, 1, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


void setup() {
  Serial.begin(115200);

  // Connect Default WiFi and Get IP Automatic
  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define IP Manually
  WiFi.config(localIP, gateway, subnet);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("You can try to ping me");
    delay(5000);
  }
}
