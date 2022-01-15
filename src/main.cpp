#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "constants.h"
#include "index_page.h" //Our HTML webpage contents


// Define the array of leds
CRGB leds[NUM_LEDS];
ESP8266WebServer server(80);
int started = 0;

//funtion to overload show because of FastLED 3.5 bug
void show(){
  FastLED.show();
  FastLED.show(); //FastLED BUG in 3.5 requires double show
}

//Web Server Functions
void handleOn() {                          
  Serial.println("on command started");
  fill_solid (leds,NUM_LEDS,CRGB::Red);
  show();
  server.sendHeader("Location","/");
  server.send(303);                   
  Serial.println("on command finished");
}

void handleLOff() {                          
  Serial.println("off command started");
  fill_solid (leds,NUM_LEDS,CRGB::Black);
  show();      
  server.sendHeader("Location","/");
  server.send(303);                         
  Serial.println("off command finished");
}

void handleColor(){

}

void handleBrightness(){

}

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void setup() {
  //setup Fast LED and initialize to black
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  fill_solid (leds,NUM_LEDS,CRGB::Black);
  show();

  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  IPAddress ip(192, 168, 0, 17); // where xx is the desired IP Address
  IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match yournetwork
  WiFi.config(ip, gateway, subnet);
  
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleLOff);
  server.on("/color", HTTP_POST, handleOn);
  server.on("/brightness", HTTP_POST, handleLOff);
  server.on("/", HTTP_GET, handleRoot);

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}

void loop() {
  server.handleClient();
}

