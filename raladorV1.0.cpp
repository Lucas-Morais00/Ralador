#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h> 

/*Pins usage & IBM Watson IoT Platform info*/
#define ORG "9e8of7" 
#define DEVICE_TYPE "ESP32-PI7" 
#define DEVICE_ID "Ralador-PI7" 
#define TOKEN "n+bOVh?*95HUfc?&7!"

/*Wifi Info*/
const char* ssid = "RM_2G";
const char* password = "RM27111803";

/*IBM Watson IoT Platform connection*/
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char pubTopic1[] = "iot-2/evt/teste1/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

int porta_A0 = A0;
int porta_D0 = 2;
int leitura_pino_analogico = 0;
int leitura_pino_digital = 0;
int buzzer = 4;
 
void setup()

    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("");
    } 

    if (!client.connected()) {
 Serial.println(server);
        while (!client.connect(clientId, authMethod, TOKEN)) {
  Serial.print(".");
            delay(500);

    }
  }

{
  pinMode(porta_A0, INPUT);
  pinMode(porta_D0, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{

  leitura_pino_analogico = analogRead(porta_A0);
  leitura_pino_digital = digitalRead(porta_D0);
  
  Serial.print("Pino Digital : ");
  Serial.print(leitura_pino_digital);
  Serial.print(" Pino Analogico : ");
  Serial.println(leitura_pino_analogico);

  if (leitura_pino_digital != 1)
  {
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(800);
    digitalWrite(buzzer, LOW);
    delay(100);
  }
  delay(100);
}
