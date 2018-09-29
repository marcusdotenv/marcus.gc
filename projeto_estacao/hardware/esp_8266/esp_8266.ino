
#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#include "wifi_script.h"

long lastmsg = 0;
int cont = 0;
int led = D3;
float dado = 0;

// ================== PROTÓTIPO DE FUNÇÕES ==================
float converte(float a);

void envia(); // envia dados para o broker.

void teste_led(); // aciona e envia o estado da lâmpada na borda de subida ou descida.

// ================== lOOP ==================
void setup(){

    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 10949);
    pinMode(led, OUTPUT);
  }


void loop(){
  if(!client.connected()){
    reconnect(); // Caso o status seja desconectado, conecte.
  }

  client.loop();

  unsigned long now = millis(); // Pega o tempo em mili de execução do algoritmo. Lembrar que isso é muito impreciso.

    if(now - lastmsg > 1000){ // Conta 1 segundo para o envio do dado
      lastmsg = now;
      envia();
      teste_led();
  }

}

// ================== FUNÇÕES ==================


  float converte(float a){
    float a_volt = (a*5)/1024;
    return a_volt;
  }

  void envia(){

    float val = analogRead(0);
    dado = converte(val);
    client.publish(leitura, String(dado).c_str(), true);
  }

  void teste_led(){
    int b = digitalRead(D3);
    if(dado >= 0.10 && b == HIGH){
      digitalWrite(led, LOW);
      client.publish(leitura, "DESLIGADO", true);
    }

     if(dado <0.10 && b == LOW){
      digitalWrite(led, HIGH);
      client.publish(leitura, "LIGADO", true);
    }
  }
