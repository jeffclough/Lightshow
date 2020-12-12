#include <WiFiNINA.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//
// Light Show
//

#define PIN 2
uint16_t PAUSING=500;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip=Adafruit_NeoPixel(16,PIN,NEO_GRB+NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

/*
class LightShow {
  Adafruit_NeoPixel *strip;

  public:
    LightShow(Adafruit_Neopixel*);
}

LightShow::LightShow(Adafruit_Neopixel *strip) {
  this->strip=strip;
}
*/


void loop() {
  uint8_t wipe_speed=0;
  /*
  uint32_t[] colors=[
    strip.Color(0xff,0,0),       // Red
    strip.Color(0xff,0x22,0),    // Orange
    strip.Color(0xff, 0xff, 0),  // Yellow
    strip.Color(0, 0xff, 0),     // Cyan
    strip.Color(0,0,0xff),       // Blue
    strip.Color(0x66,0,0xff),    // Purple
    strip.Color(0xff,0,0xff),    // Magenta
    strip.Color(0xff,0xff,0xff)  // White
  ];
  */

  // Some example procedures showing how to display to the pixels:
  if (true) {
    wipe_speed=1;
    PAUSING=750;
    delay(PAUSING); colorWipe(strip.Color(0xff,0,0), wipe_speed);           // Red  
    delay(PAUSING); colorReverseWipe(strip.Color(0xff,0x22,0), wipe_speed); // Orange
    delay(PAUSING); colorWipe(strip.Color(0xff,0xff,0), wipe_speed);        // Yellow
    delay(PAUSING); colorReverseWipe(strip.Color(0,0xff,0), wipe_speed);    // Green
    delay(PAUSING); colorWipe(strip.Color(0,0x88,0x88), wipe_speed);        // Cyan
    delay(PAUSING); colorReverseWipe(strip.Color(0,0,0xff), wipe_speed);    // Blue
    delay(PAUSING); colorWipe(strip.Color(0xff,0,0xff), wipe_speed);        // Magenta
    delay(PAUSING); colorReverseWipe(strip.Color(0x44,0,0xff), wipe_speed); // Purple
    delay(PAUSING); colorWipe(strip.Color(0xff,0xff,0xff), wipe_speed);     // White
    delay(PAUSING); colorReverseWipe(strip.Color(0,0,0), wipe_speed);       // Black
  }
  else {
    wipe_speed=1500/16;
    PAUSING=1000;
    delay(PAUSING); colorWipe(strip.Color(0,0xff,0), wipe_speed);              // Green
    delay(PAUSING); colorReverseWipe(strip.Color(0x44,0,0xff), wipe_speed);    // Purple
    delay(PAUSING); colorWipe(strip.Color(0xff,0xff,0xff), wipe_speed);        // White
    delay(PAUSING); colorReverseWipe(strip.Color(0,0xff,0), wipe_speed);       // Green
    delay(PAUSING); colorWipe(strip.Color(0x44,0,0xff), wipe_speed);           // Purple
    delay(PAUSING); colorReverseWipe(strip.Color(0xff,0xff,0xff), wipe_speed); // White
  }

  // Send a theater pixel chase in...
  //theaterChase(strip.Color(0x80, 0x80, 0x80), 50); // White
  //theaterChase(strip.Color(0x80, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 0x80), 50); // Blue

  //rainbow(60);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other, clockwise, with a color
void colorReverseWipe(uint32_t c, uint8_t wait) {
  for(int16_t i=strip.numPixels()-1; i>=0; i--) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//
// Web Service
//

#define SERIAL_OUTPUT

#include "arduino_secrets.h"

char ssid[]=SECRET_WIFI_SSID;  // your network SSID (name)
char pass[]=SECRET_WIFI_PASS;  // your network password (use for WPA, or use as key for WEP)
int status=WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize the lights.
  strip.begin();
  strip.setBrightness(0x10);
  strip.show(); // Initialize all pixels to 'off'

  // Connect to WiFi
  if (WiFi.status()==WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // We're dead!
  }
  String fv = WiFi.firmwareVersion();
  if (fv<WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  // Connect.
  Serial.print("Trying to connect to WPA SSID: ");
  Serial.println(ssid);
  while (status!=WL_CONNECTED) {
    Serial.print(".");
    status=WiFi.begin(ssid,pass);
    delay(1000);
  }
  // We're connected!
  Serial.print("You're connected to the network!");
  printCurrentNet();
  printWifiData();
}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }

  Serial.println();
}
