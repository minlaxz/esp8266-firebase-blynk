/*
Copyright (c) 2018,June by Min Min Latt (laxzoncloud)
Based on the SSD1306 OLED library Copyright (c) 2015 by Daniel Eichhorn (http://blog.squix.ch),
available at https://github.com/squix78/esp8266-oled-ssd1306

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

This Arduino File (ino) is aimed for using ESP8266-12E module (nodemcu DevKit V1.0)
OLED Display (Display Driver - SH1106) Spi interface via connection with
Nodemcu.
Read DHT11 Sensor and monitor at oled display.

Hardware Wemos D1 mini SPI pins
 D5 GPIO14   CLK         - D0 pin OLED display
 D6 GPIO12   MISO (DIN)  - not connected
 D7 GPIO13   MOSI (DOUT) - D1 pin OLED display
 D1 GPIO5    RST         - RST pin OLED display
 D2 GPIO4    DC          - DC pin OLED
 D8 GPIO15   CS / SS     - CS pin OLED display
*/

#include <Wire.h>
#include <SPI.h>
#include "SH1106.h"
#include "SH1106Ui.h"
#include "images.h"
#include "DHT.h"

#define OLED_RESET  D1   // RESET
#define OLED_DC     D2   // Data/Command
#define OLED_CS     D8   // Chip select
#define DHTPIN 2         // DHT11 OUT
#define DHTTYPE DHT11   // DHT 11

SH1106 display(true, OLED_RESET, OLED_DC, OLED_CS); // FOR SPI
SH1106Ui ui     ( &display );

bool msOverlay(SH1106 *display, SH1106UiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(millis()/1000));
  return true;
}

bool drawFrame1(SH1106 *display, SH1106UiState* state, int x, int y) {
  display->drawXbm(x + 34, y + 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  return false;
}

bool drawFrame2(SH1106 *display, SH1106UiState* state, int x, int y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawStringMaxWidth(1 + x, 10 + y, 128, "This demo is modified by Min Min Latt ('laxzoncloud')");
  return false;
}

bool drawFrame3(SH1106 *display, SH1106UiState* state, int x, int y) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0 + x, 10 + y, "laxz 10");

  display->setFont(ArialMT_Plain_16);
  display->drawString(0 + x, 20 + y, "laxz 16");

  display->setFont(ArialMT_Plain_24);
  display->drawString(0 + x, 34 + y, "laxz 24");
  return false;
}

bool drawFrame4(SH1106 *display, SH1106UiState* state, int x, int y) {
  DHT dht(DHTPIN, DHTTYPE);
  delay(1000);
  float h = dht.readHumidity();
  //float t = dht.readTemperature();
  
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64+x,22,"Humidity:" + String(h));
  
  return false;
}


int frameCount = 4;
bool (*frames[])(SH1106 *display, SH1106UiState* state, int x, int y) = { drawFrame1, drawFrame2, drawFrame3, drawFrame4 };
bool (*overlays[])(SH1106 *display, SH1106UiState* state)             = { msOverlay };
int overlaysCount = 1;

void setup() {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  
  ui.setTargetFPS(30);
  ui.setActiveSymbole(activeSymbole);
  ui.setInactiveSymbole(inactiveSymbole);
  ui.setIndicatorPosition(BOTTOM);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_RIGHT);
  ui.setFrames(frames, frameCount);
  ui.setOverlays(overlays, overlaysCount);
  ui.init();
  display.flipScreenVertically();
}

void loop() {
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    // Something 
    delay(remainingTimeBudget);
  }
}

