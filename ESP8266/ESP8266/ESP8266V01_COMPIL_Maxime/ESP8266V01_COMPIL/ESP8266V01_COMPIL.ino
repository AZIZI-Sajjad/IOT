#include "WiFiClient.h"
#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "ESP8266Ping.h"
#include "ArduinoJson.h"

WiFiClient wifiClient;

ESP8266WebServer server(80);
String pingip, avg_ms_str, link, getData;
int avg_ms;
int Ipin;
int timer;
int pinsState [9];
int OldpinsState;
const byte pins [9] = {16, 5, 4, 0, 2, 14, 12, 13, 15};

String device = "DEVICE_SERIAL_NUMBER";
String codevers = "V2";
String devType = "IO";
String devMode = "active";
String lcdPresent = "non";

const unsigned long HTTP_TIMEOUT = 10000;

void setup() {
 
  Serial.begin(9600);
  WiFi.begin("M0!", "%$P@ssw0rdHuawei");  //Connect to the WiFi network
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
    delay(500);
    Serial.println("Waiting to connect…");
 
  }

  //DEBUG COMMAND
  //Serial.print(resource);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
  String LanIP = WiFi.localIP().toString();
  server.on("/", handleRootPath);    //Associate the handler function to the path
  server.begin();                    //Start the server
  Serial.println("Server listening");

}
 
void loop() {
 
  server.handleClient();         //Handling of incoming requests
  //TON CODE ICI
  
  delay(1);
}
 
void handleRootPath() {            //Handler for the rooth path
 
  server.send(200, "text/plain", "AH26 POLLER (JSON VERSION) "+device+" Please contact maxime.darbas@ah26.fr for more informations");
 
}
