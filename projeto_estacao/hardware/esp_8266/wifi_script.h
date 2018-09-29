#include<ESP8266WiFi.h>
#include<PubSubClient.h>

#define wifi_ssid "Katia_Bronze"
#define wifi_password "bronze18"


#define mqtt_server "m15.cloudmqtt.com"
#define mqtt_user "ssnqowmf"
#define mqtt_password "lgAui-jxuz9k"

#define leitura "/mqtt/leitura"
#define estado_led "/mqtt/estado"

WiFiClient espClient;
PubSubClient client(espClient);

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
    if(client.connect("ESP8266Client", mqtt_user, mqtt_password)){
      Serial.println("Conectado"); // Conecta ao broker
    } else{
      Serial.println("FALHA");
      Serial.println(client.state());
      Serial.println("Tente novamente após 5 segundos");

      delay(5000);
    }
  }
}
