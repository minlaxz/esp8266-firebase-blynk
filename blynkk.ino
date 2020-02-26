#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define WiFi_SSID "laxz10xx"
#define WiFi_PASSWORD "password"

char auth[] = "--blynkauth--";
char ssid[] = WiFi_SSID;
char pass[] = WiFi_PASSWORD;

const int ledPin = 12;
const int btnPin = 8;

BlynkTimer timer;
void checkPhysicalButton();

int ledState = LOW;
int btnState = HIGH;


BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V2);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V2) {
  ledState = param.asInt();
  digitalWrite(ledPin, ledState);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState != LOW) {

      // Toggle LED state
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      // Update Button Widget
      Blynk.virtualWrite(V2, ledState);
    }
    btnState = LOW;
  } else {
    btnState = HIGH;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth,ssid, pass);
  WiFi.begin(WiFi_SSID,WiFi_PASSWORD);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(ledPin, ledState);

  // Setup a function to be called every 100 ms
  timer.setInterval(100L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}
