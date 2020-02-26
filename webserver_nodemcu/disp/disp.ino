#include "SH1106.h"
#include <DHT.h>

#define OLED_RESET  D1   // RESET
#define OLED_DC     D2   // Data/Command
#define OLED_CS     D8   // Chip select
#define DHTPIN 2         // DHT11 OUT
#define DHTTYPE DHT11   // DHT 11

SH1106 display(true, OLED_RESET, OLED_DC, OLED_CS);

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  dht.begin(); // initialize dht
}
void displayTempHumid(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(t);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)){
    display.clear(); // clearing the display
    display.drawString(5,0, "Failed DHT");
    return;
  }
  display.clear();
  display.drawString(0, 0, "Humidity: " + String(h) + "%"); 
  display.drawString(0, 16, "Temp: " + String(t) + "C"); 
  if (t > 35.0){
    display.drawString(0,32, "Warning Temperature! Alarm Active.");
  }
  else{
    display.drawString(0,32, "Good Temperature.No Alarm.");
  }
  
  display.drawString(0, 48, "Made By Min Min Latt"); 
}
void loop(){
  displayTempHumid();
  display.display();
  delay(2000);
}
