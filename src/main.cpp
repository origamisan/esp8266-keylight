#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// How many leds in your strip?
#define NUM_LEDS 10


// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN D1

// Define the array of leds
CRGB leds[NUM_LEDS];
const char* ssid     = "the_good_wifi";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "forkinshirtballs";
ESP8266WebServer server(80);
int x =0;

void handleLED() {                          // If a POST request is made to URI /LED
  Serial.println("command");
  //int hue = server.arg("value").toInt();
  //StaticColor(CHSV(125 , 255, 255));       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(200);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
  //FastLED.show();
}

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(10);
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

  server.on("/LED", HTTP_GET, handleLED);
  //server.on("/off", HTTP_GET, handleLEDoff);
  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}

void loop() {
  server.handleClient();
  // Serial.println(x);
  // // Turn the LED on, then pause
  // fill_solid (leds,10,CRGB::Blue);
  // FastLED.show();
  // delay(1000);
  // // Now turn the LED off, then pause
  // fill_solid (leds,10,CRGB::Black);
  // //FastLED.show();
  // delay(1000);
  // x++;
}

