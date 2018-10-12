# Documentação do algoritmo subscriber do Raspberry Pi

O algoritmo em Python disponível [aqui](https://github.com/Marcusharu/marcus.gc/blob/master/projeto_estacao/servidor/raspberrypi/subscriber.py) conecta um Raspberry Pi a um broker na nuvem e recebe os dados para enviá-los para um banco de dados MySQL.


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



# Funções:
O algoritmo descrito abaixo trata-se de um subscriber descrito no protocolo MQTT.

Ele recebe as informações publicadas pelo publisher no broker e faz a alocação desses dados no banco de dados.


> def on_connect(client, userdata, flags, rc):

Essa função conecta ao broker mqtt. Seus parâmetros são:

1. Client: Instância do client criada.

2. Userdata: Os dados do usuário setados no Client();

3. Flags: Flags de resposta enviadas pelo  broker;

4. rc: código resposta sobre em resultado da tentativa de conexão.

Possíveis valores de RC:

0: Conectado com sucesso;

1: Conexão recusada: versão do protocolo incorreta;

2: Conexão recusada: Identificador de client inválido;

3: Conexão recusada: server indisponível;

4: Conexão recusada: erro de username ou password;

5: Conexão recusada: Não autorizado;

6-255: Erro desconhecido.


Por fim, essa função inscreve o subscriber no tópico desejado.


> def on_message(client, userdata, msg)


Essa função diz o que será feito quando o subscriber receber um dado.
Talvez ela tenha ficado um pouco extensa e seja mais viável alterar o que ela faz a fim de separar a parte de recebimento de dados e de alocação no banco de dados. Todavia, atualmente está funcional.


Dependendo do nome do tópico publicado, o algoritmo aloca o dado recebido em alguma posição do banco de dados. Utilizei para comparação as 3 primeiras letras de cada tópico, uma vez que, até ali todos os tópicos são iguais no seguinte modelo:

"/mqtt/tópico"

O comando em PHP atribuído a variável string "sql" dá ao comando "cursor.execute", da bilbioteca MySQL, o parâmetro necessário para enviar ao banco de dados os dados nas tabelas corretas. Sendo sua sintaxe:

INSERT INTO 'TABELA' (coluna1, coluna2, coluna3) VALUES (valor1, valor2, valor3).
