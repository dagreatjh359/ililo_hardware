#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <RCSwitch.h>
#define ID "35" // tx = 33 rx 34 35 36 37
#define LED 2

const char* ssid = "AndroidHotspotjh";
const char* password = "35903190";
String host = "http://13.209.179.119";
String near_id;
String near_id_tmp;

const long interval = 1000;
const long interval_d = 3000;
unsigned long previousMillis = 0;
WiFiServer server(80);
WiFiClient client;
HTTPClient http;

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #3
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("init");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop() {
  if (mySwitch.available()) {

    Serial.print("Received ");
    Serial.print(mySwitch.getReceivedValue());
    Serial.print(" / ");
    Serial.print(mySwitch.getReceivedBitlength());
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println(mySwitch.getReceivedProtocol());

    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(2000);

    near_id_tmp = mySwitch.getReceivedValue();
    near_id = near_id_tmp;

    mySwitch.resetAvailable();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      //near_device_id 송신 받은 값, device_id 내 아이디는 지정된 것
      String phpHost = host + "/insert.php?nearid=" + ID + "&ID=" + String(near_id_tmp);
      Serial.print("Connect to ");
      Serial.println(phpHost);

      http.begin(client, phpHost);
      http.setTimeout(1000);
      int httpCode = http.GET();

      while(httpCode<0){
        httpCode = http.GET();
        Serial.println("not a good httpCode.");
      }

      if (httpCode > 0) {
        Serial.printf("GET code : %d\n\n", httpCode);

        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("GET failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval_d) {
      previousMillis = currentMillis;
      String phpHost = host + "/delete.php?nearid=" + ID + "&ID=" + String(near_id);
      Serial.print("Connect to ");
      Serial.println(phpHost);

      http.begin(client, phpHost);
      http.setTimeout(1000);
      int httpCode = http.GET();

      while(httpCode<0){
        httpCode = http.GET();
        Serial.println("not a good httpCode.");
      }

      if (httpCode > 0) {
        Serial.printf("GET code : %d\n\n", httpCode);

        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("GET failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
  }
}