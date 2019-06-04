#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
const char* ssid = "Aceself_home_1001U";
const char* password = "12345678";
ESP8266WebServer server(80);
int stateDevice1 = LOW;
int stateDevice2 = LOW;
int stateDevice3 = LOW;
int stateDevice4 = LOW;
#define RELAY1 D0
#define RELAY2 D1
#define RELAY3 D2
#define RELAY4 D3

void handleRoot() {
    response();
}

void handleDevice1On() {
  stateDevice1 = HIGH;
  if(digitalRead(RELAY1)==LOW){
    digitalWrite(RELAY1, stateDevice1);
  }else{
    response();
  }

  response();
}

void handleDevice1Off() {
  stateDevice1 = LOW;
  if(digitalRead(RELAY1)==HIGH){
    digitalWrite(RELAY1, stateDevice1);
  }else{
    response();
  }

  response();
}
void handleDevice2On() {
  stateDevice2 = HIGH;
  digitalWrite(RELAY2, stateDevice2);
  response();
}

void handleDevice2Off() {
  stateDevice2 = LOW;
  digitalWrite(RELAY2, stateDevice2);
  response();
}
void handleDevice3On() {
  stateDevice3 = HIGH;
  digitalWrite(RELAY3, stateDevice3);
  response();
}

void handleDevice3Off() {
  stateDevice3 = LOW;
  digitalWrite(RELAY3, stateDevice3);
  response();
}
void handleDevice4On() {
  stateDevice4 = HIGH;
  digitalWrite(RELAY4, stateDevice4);
  response();
}

void handleDevice4Off() {
  stateDevice4 = LOW;
  digitalWrite(RELAY4, stateDevice4);
  response();
}
const String HtmlHtml = "<html><head>"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
    const String HtmlHtmlClose = "</html>";
    const String HtmlTitle = "<h1>Aceself Home Automation Demo</h1><br/>\n";
    const String HtmlLedState1Low = "<big>LED is now <b>OFF</b></big><br/>\n";
    const String HtmlLedState1High = "<big>LED is now <b>ON</b></big><br/>\n";
    const String HtmlLedState2Low = "<big>LED is now <b>OFF</b></big><br/>\n";
    const String HtmlLedState2High = "<big>LED is now <b>ON</b></big><br/>\n";
    const String HtmlLedState3Low = "<big>LED is now <b>OFF</b></big><br/>\n";
    const String HtmlLedState3High = "<big>LED is now <b>ON</b></big><br/>\n";
    const String HtmlLedState4Low = "<big>LED is now <b>OFF</b></big><br/>\n";
    const String HtmlLedState4High = "<big>LED is now <b>ON</b></big><br/>\n";
    const String HtmlButtons =
    "<a href=\"LED1On\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"LED1Off\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"
    "<a href=\"LED2On\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"LED2Off\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"
    "<a href=\"LED3On\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"LED3Off\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"
    "<a href=\"LED4On\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"LED4Off\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>";

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(digitalRead(RELAY1) == LOW){
    htmlRes += HtmlLedState1Low;
  }else{
    htmlRes += HtmlLedState1High;
  }
  if(stateDevice2 == LOW){
    htmlRes += HtmlLedState2Low;
  }else{
    htmlRes += HtmlLedState2High;
  }
  if(stateDevice3 == LOW){
    htmlRes += HtmlLedState3Low;
  }else{
    htmlRes += HtmlLedState3High;
  }
  if(stateDevice4 == LOW){
    htmlRes += HtmlLedState4Low;
  }else{
    htmlRes += HtmlLedState4High;
  }
  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {

  pinMode(RELAY1, OUTPUT);
   digitalWrite(RELAY1, LOW);

        pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, LOW);

        pinMode(RELAY3, OUTPUT);
  digitalWrite(RELAY3, LOW);

        pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY4, LOW);

  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(WiFi.softAPIP());
  String ipString = WiFi.softAPIP().toString();
  Serial.println(ipString);

  server.on("/", handleRoot);
  server.on("/LED1On", handleDevice1On);
  server.on("/LED1Off", handleDevice1Off);
  server.on("/LED2On", handleDevice2On);
  server.on("/LED2Off", handleDevice2Off);
  server.on("/LED3On", handleDevice3On);
  server.on("/LED3Off", handleDevice3Off);
  server.on("/LED4On", handleDevice4On);
  server.on("/LED4Off", handleDevice4Off);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

}
