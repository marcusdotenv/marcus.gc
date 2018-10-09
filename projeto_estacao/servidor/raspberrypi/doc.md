# Documentação do algoritmo subscriber do Raspberry Pi

O algoritmo em Python disponível [aqui](subscriber.py) conecta um Raspberry Pi a um broker na nuvem e recebe os dados para enviá-los para um banco de dados MySQL.


São as bibliotecas utilizadas:

1. *Paho.mqtt.client*:

Clique [aqui](https://github.com/eclipse/paho.mqtt.python) para fazer o download.

Biblioteca utilizada para utilizar as funções mqtt em Python. Há uma vasta documentação sobre essa biblioteca clicando [aqui](http://www.steves-internet-guide.com/into-mqtt-python-client/).



2. *sys*:

Biblioteca já inclusa no python. Para este algoritmo ela é responsável pela utilização das funçõesde tratamento de exceção try e except. Além disso, fornece uma saída para a execução do sistema ao apertar ctrl+C.


3. *MySQLdb*:

Inclui as funções MySQL dentro do algoritmo. Possibilitando subir os dados recebidos em tabelas no banco de dados.


4. *Time*:

Biblioteca já inclusa no python que serve para fazer a contagem do tempo sincronizado com a hora do dispositivo que você está utilizando.
