# Documentação do algoritmo de medição

CLique [aqui](esp_8266.ino) para ter acesso ao algoritmo de medição e [aqui](wifi_script.h) para ter acesso ao algoritmo de conexão Wifi.

São utilizadas as bibliotecas :


1. *PubSubClient.h* -

Responsável por acrescentar as funções MQTT ao ESP8266. Incluindo as funções de publicação e inscrição.

Para download, clique [aqui](https://github.com/knolleary/pubsubclient).

2. *ESP8266WIFI* -

Configura a rede Wifi na qual o ESP8266 está conectado e mantém a conexão.

Para download, clique [aqui](https://github.com/ekstrand/ESP8266wifi).
Há também uma boa documentação sobre como funciona essa bliblioteca. Para ter acesso, clique [aqui](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html).


3. *Biblioteca DHT* -

Coordena o sensor DHT11 e acrescenta as funções necessárias para a utlização do sensor.

Clique [aqui](https://github.com/adafruit/DHT-sensor-library) para download da biblioteca.


## Funções

1. *Bloco Operações Matemáticas*:

Funções auxiliares que servem para operações matemáticas dentro do código.

> 1. float converte(float a);

Essa função recebe um valor lido em uma entrada analógica do módulo ESP8266 e converte seu valor para tensão. No caso do dado de luminosidade, poderia ser feito ainda a conversão para a unidade Lux. Entretanto, achei essa unidade pouco perceptível. Naturalmente, converte-lo para um valor percentual de luminosidade me pareceu mais intuitivo e agradável para a leitura do usuário.

2. *Bloco Envio de Dados*:

As funções desse bloco fazem a comunicação do sensor com o broker através do sistema de publish e subscribe do protocolo MQTT.

> 1. void envia_luminosidade();

Chama a função converte() e da um publish em um determinado tópico contendo o resultado de luminosidade percentual obtido. O dado publicado é convertido para string nesse processo.


> 2. void envia_temperatura();

Essa função atribui a uma variável o valor lido pelo sensor DHT11. É importante dizer que este sensor é digital, e portanto, os dados são passados sem a necessidade de nenhum tratamento especial. Portanto, basta apenas publicar o dado após obtê-lo.


> 3. void envia_umidade();

Assim como a função acima, trabalha com a bilbioteca do DHT11 e publica um dado em um tópico.


3. *Bloco Funções Comentadas:*

São funções que foram idealizadas e em algum momento foram implementadas e testadas durante o desenvolvimento do algoritmo, porém, foram descartadas por alguma razão.


> 1. void test_borda();

Essa função lê o valor de uma porta digital a fim de descobrir se seu estado é HIGH ou LOW. Em seguida, muda e publica o estado atual da porta digital apenas se o estado atual for diferente do próximo estado.
Essa função servia para acender e apagar uma lâmpada dependendo do valor de luminosidade dado pela função envia_luminosidade(), permitindo enviar ao broker apenas uma vez o estado da lâmpada caso este fosse trocado. Porém, essa funcionalidade foi descartada.

4. *Bloco Função Principal:*

O loop consiste em chamar a função reconnect() caso a conexão wifi tenha sido perdida, a fim de reestabelecê-la.

Além disso, dois contadores, *unsigned long*, pegam o valor da função millis() a fim de controlar o tempo em que os dados são enviados. Os dados de luminosidade são enviados uma vez a cada segundo. Enquanto os dados de temperatura e umidade uma vez a cada 2 minutos.

Até o momento esses tempos foram arbitrários e não necessariamente condizem com os tempos ideais para que a amostragem de dados seja suficiente para se produzir analises sobre os dados. No futuro, será necessário conduzir um breve estudo sobre isso. Além disso, a função millis() não é suficientemente confiável para precisão, uma vez que, o início de sua contagem se dá quando o algoritmo inicia sua execução e essa função nunca para de contar.



# Documentação do algoritmo Wifi e MQTT

São utilizadas as mesmas bibliotecas que anteriormente foram citadas. Agora, nesse algoritmo, em primeiro momento temos a definição de vários parâmetros que serão usados durante a execução.



Não há muitas particularidades nesse algoritmo. Apenas é importante se atentar a preencher corretamente os parâmetros das funções Wifi e MQTT. 
