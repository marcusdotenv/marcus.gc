#include<ESP8266WiFi.h>
#include<PubSubClient.h>

#define wifi_ssid "Katia_Bronze"
#define wifi_password "bronze18"


#define mqtt_server "iot.eclipse.org"
#define mqtt_user "ssnqowmf"
#define mqtt_password "lgAui-jxuz9k"
#define mqtt_id "M32"

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
