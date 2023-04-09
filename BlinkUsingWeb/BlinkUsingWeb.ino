
#include <WiFi.h>

const char* ssid = "Mantul-L1";         //"Jojo";
const char* password = "ManToel$578$";  //"MauTauAja";
const int LED_PIN = 23;

// Configure IP Address of the local access point
const IPAddress localIP(192, 168, 5, 150);
const IPAddress gateway(192, 168, 5, 1);
const IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

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

  server.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 23 ON.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 23 OFF.<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) digitalWrite(LED_PIN, HIGH);
        if (currentLine.endsWith("GET /L")) digitalWrite(LED_PIN, LOW);
      }
    }
    client.stop();
    Serial.println("Client Disconnected!");
  }
}
