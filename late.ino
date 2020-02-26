
#define BLYNK_PRINT Serial
#define WiFi_SSID "laxz00xx"
#define WiFi_PASSWORD "password"
#define DHTPIN 2
#define DHTTYPE DHT11

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "--blynkauth";
char ssid[] = WiFi_SSID;
char pass[] = WiFi_PASSWORD;
DHT dht(DHTPIN, DHTTYPE);
int led = 12;

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); 
  Serial.println(pinValue);
  digitalWrite(led, pinValue);
  if(pinValue==1){
    Blynk.virtualWrite(V0,255);
  }else{
    Blynk.virtualWrite(V0,0);
  }
}

void setup()
{
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(WiFi_SSID,WiFi_PASSWORD);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected");
  Serial.println(WiFi.localIP());
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)){
    delay(100);
    return;
  }
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
  Blynk.run();
  delay(100);
  
}
