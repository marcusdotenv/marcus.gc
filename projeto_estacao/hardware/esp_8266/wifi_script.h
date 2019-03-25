#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#include<DHT.h>

// ============ Configurações WiFi ==============
#define wifi_ssid ""
#define wifi_password ""

// ============ Configurações mqtt ==============
#define mqtt_server ""
#define mqtt_user ""
#define mqtt_password ""
#define mqtt_id ""

// ============ Configurações tópicos ==============
#define luminosidade "/mqtt/luminosidade"
#define temperatura "/mqtt/temperatura"
#define umidade "/mqtt/umidade"

// ============ Configurações DHT ==============
#define DHT_PINO D7
#define DHT_TIPO DHT11

// ============ Configurações objetos ==============
WiFiClient espClient;
PubSubClient client(espClient);

DHT TH_sensor(DHT_PINO, DHT_TIPO);

void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Conectando...");
  Serial.println(wifi_ssid);


  WiFi.begin(wifi_ssid, wifi_password);

  while(WiFi.status() != WL_CONNECTED){ // printa pontos enquanto não conecta
    delay(500);
    Serial.print(".");
  }
}
void reconnect(){

  while(!client.connected()){
    Serial.print("Tentando MQTT...");
    if(client.connect(mqtt_id)){
      Serial.println("Conectado"); // Conecta ao broker
    } else{
      Serial.println("FALHA");
      Serial.println(client.state());
      Serial.println("Tente novamente após 5 segundos");

      delay(5000);
    }
  }
}
