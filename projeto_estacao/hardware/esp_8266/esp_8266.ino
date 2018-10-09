
#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#include "wifi_script.h"
#include<DHT.h>

unsigned long lastmsg = 0;
unsigned long lastmsg2 = 0;
int cont = 0;
int led = D3;
float dado = 0;

DHT TH_sensor(DHT_PINO, DHT_TIPO);




// ================== PROTÓTIPO DE FUNÇÕES ==================
float converte(float a);

void envia_luminosidade(); // envia dados para o broker.
void envia_temperatura();
void envia_umidade();

void teste_led(); // aciona e envia o estado da lâmpada na borda de subida ou descida.

// ================== lOOP ==================
void setup(){

    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    pinMode(led, OUTPUT);
    TH_sensor.begin();
  }


void loop(){
  if(!client.connected()){
    reconnect(); // Caso o status seja desconectado, conecte.
  }

  client.loop();

  unsigned long now = millis(); // Pega o tempo em mili de execução do algoritmo. Lembrar que isso é muito impreciso.
  unsigned long now2 = millis();

    if(now - lastmsg > 1000){ // Conta 1 segundo para o envio do dado
      lastmsg = now;
      envia_luminosidade();
  }
  if(now2 - lastmsg2 > 120000){
    lastmsg2 = now2;
    envia_temperatura();
    envia_umidade();
  }

}

// ================== FUNÇÕES ==================


  float converte(float a){
    float a_volt = (a*5)/1024;
    return a_volt;
  }

  void envia_luminosidade(){

    float val = analogRead(0);
    dado = converte(val);
    client.publish(luminosidade, String(dado).c_str(), true);
  }

  void envia_temperatura(){
    float t = TH_sensor.readTemperature();
    client.publish(temperatura, String(t).c_str(), true);
    Serial.println(t);
  }
  void envia_umidade(){
    float u = TH_sensor.readHumidity();
    client.publish(umidade, String(u).c_str(), true);
    Serial.println(u);

  }

/*  void teste_led(){
    int b = digitalRead(D3);  PARTE QUE PODE SER ADICIONADA DEPOIS
    if(dado >= 0.10 && b == HIGH){
      digitalWrite(led, LOW);
      client.publish(leitura, "DESLIGADO", true);
    }

     if(dado <0.10 && b == LOW){
      digitalWrite(led, HIGH);
      client.publish(leitura, "LIGADO", true);
    }
  } */
