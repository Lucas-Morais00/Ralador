/* Projeto Integrador 7 - Ralador de Isopor*/
/* BEC & BEP*/

/* Org ID: 9e8of7 */
/* Device: ID: PI7 */
/* Token: AxHfR&E!I&?j(KRi0j */

/* Instalar PubSubClient */

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h> 

#define ORG "9e8of7" 
#define DEVICE_TYPE "ESP8266" 
#define DEVICE_ID "PI7" 
#define TOKEN "AxHfR&E!I&?j(KRi0j"

const char* ssid = "F3.RM";
const char* password = "rm180293";

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char pubTopic1[] = "iot-2/evt/status1/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

int vs = 2;

long vibration() {
  long medida = pulseIn(vs, HIGH);
  return medida;
}

void setup() {

    pinMode(vs, INPUT);
    Serial.begin(115200);

    Serial.println();
    Serial.print("Connecting to "); 
    Serial.print(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    
    Serial.print("WiFi connected, IP address: "); 
    Serial.println(WiFi.localIP());

    if (!client.connected()) {
        Serial.print("Reconnecting client to ");
        Serial.println(server);
        while (!client.connect(clientId, authMethod, token)) {
            Serial.print(".");
            delay(500);
        }
        Serial.println("Bluemix connected");
    }
}

long lastMsg = 0;

void loop() {
    client.loop();
    long now = millis();
    if (now - lastMsg > 3000) {
        lastMsg = now;
    
    long medida = vibration();
    delay(500);

        /* Calcular sensor */
        int vibracao = medida;
        
        String payload = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
              payload += ",\"vibracao\":";
              payload += vibracao;
              payload += "}}";
       
        Serial.print("Sending payload: ");
        Serial.println(payload);

        if (client.publish(pubTopic1, (char*) payload.c_str())) {
            Serial.println("Publish ok");
        } else {
            Serial.println("Publish failed");
        }
    }
}
