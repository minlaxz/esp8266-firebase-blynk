#include <ESP8266WiFi.h>
#include <string.h>
#include <stdio.h>
#define     LED0      2
#define     LED1      D0
#define     LED2      D8

int sen_1,sen_2;
char*       get_ssid;
char*       get_password;
int LEDState = LOW;
WiFiServer  VARServer(9001);
WiFiClient  TKDClient;

void setup()
{
  Serial.begin(115200);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  
  SetWifi("ElectronicWings", "");
}
  
void loop()
{
  IsClient();
}
  
void SetWifi(char* Name, char* Password)
{
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  Serial.println("WIFI Mode : AccessPoint Station");
  get_ssid      = Name;
  get_password  = Password;
  WiFi.softAP(get_ssid, get_password);
  Serial.print("WIFI <" + String(get_ssid) + "> started and ");
  Serial.println("Password is <" + String(get_password)+">");
  delay(1000);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AccessPoint IP is : ");
  Serial.println(IP);
  VARServer.begin();
  Serial.println("Server Started");
}

void IsClient()
{
  if(VARServer.hasClient())
  {
    WiFiClient TKDClient = VARServer.available();
    if(digitalRead(LED0) == HIGH) digitalWrite(LED0, LOW);
    digitalWrite(LED1, HIGH);
    Serial.println("Accepted incoming connection from specific ESP Client");
    while(1)
    {
        if(TKDClient.available())
        {
          String Message = TKDClient.readStringUntil('\r');
          //Serial.print("MPU2: ");Serial.println(Message.substring(1,2)); //to get only one char from client without decided what char is.
          if(Message.substring(1,2).equals("k")){sen_2 = 1; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("l")){sen_2 =2 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("m")){sen_2 =3 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("n")){sen_2 =4 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("o")){sen_2 =5 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("p")){sen_2 =6 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("q")){sen_2 =7 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("r")){sen_2 =8 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("s")){sen_2 =9 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("t")){sen_2 =10 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
          else {sen_2 =0 ; Serial.print("MPU2: ");Serial.println(sen_2);
          //--------------------------------
          }
       

          Message = TKDClient.readStringUntil('\r');
          //Serial.print("MPU1: ");Serial.println(Message.substring(1,2));
          if(Message.substring(1,2).equals("a")){sen_1 = 1; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("b")){sen_1 =2 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("c")){sen_1 =3 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("d")){sen_1 =4 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("e")){sen_1 =5 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("f")){sen_1 =6 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("g")){sen_1 =7 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("h")){sen_1 =8 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("i")){sen_1 =9 ; Serial.println(sen_1);
          //--------------------------------
          }
          else if(Message.substring(1,2).equals("j")){sen_1 =10 ; Serial.println(sen_1);
          //--------------------------------
          }
          else {sen_1 =0 ; Serial.println(sen_1);
          //--------------------------------
          }delay(10);
          
        }

        if(!TKDClient || !TKDClient.connected())
        {
          digitalWrite(LED1, LOW);
          break;
        }

      }
      
    } 
    else
    {
      // This LED Blinks If No Clients Where Available
      digitalWrite(LED0, HIGH);
      delay(250);
      digitalWrite(LED0, LOW);
      delay(250);
    }
  }
