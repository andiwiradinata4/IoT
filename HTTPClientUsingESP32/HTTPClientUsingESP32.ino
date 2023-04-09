
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "Mantul-L1";         //"Jojo";
const char* password = "ManToel$578$";  //"MauTauAja";
const int LED_PIN = 23;

// Configure IP Address of the local access point
// const IPAddress localIP(192, 168, 5, 150);
// const IPAddress gateway(192, 168, 5, 1);
// const IPAddress subnet(255, 255, 255, 0);
const String baseUrl = "https://dev.alpagogo.com";
const String urlLogin = "/api/v1/auth/login";

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

  pinMode(LED_PIN, OUTPUT);




  // Process Login
  String body = "";
  StaticJsonDocument<256> json;
  json["email"] = "andiwiradinata4@gmail.com";
  json["password"] = "Mantul#0001";
  serializeJson(json, body);

  HTTPClient httpClient;
  httpClient.begin(String(baseUrl) + String(urlLogin));
  httpClient.addHeader("Content-Type", "application/json");
  httpClient.addHeader("api-key", "django-insecure-&#!v3ws_myd_7xvb+93+kxj4mtnv)qa3%gkf%+m_et7^_babq_");

  int intResponseCode = httpClient.POST(body);
  Serial.println("HTTP Response Code: " + String(intResponseCode));

  if (intResponseCode > 0) {
    String payload = httpClient.getString();
    Serial.print(payload);
    digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println("Error on HTTP Request");
  }
  httpClient.end();
  delay(5000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
}
