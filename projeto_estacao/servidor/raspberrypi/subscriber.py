# Recebe o dado e envia para o Banco

# Bibliotecas

import paho.mqtt.client as mqtt
import sys
import MySQLdb
import time

#  DB config
db_adress = "localhost"
db_login = "root"
db_passwd = "raspberry"
db_name = "ML"

#MQTT config

br_adress = "iot.eclipse.org"
br_port = 1883
br_keep = 60
topic = "/mqtt/#"

# Conecta com o banco
try:
    db = MySQLdb.connect(db_adress,db_login,db_passwd,db_name)
except:
    print("Sem acesso ao banco de dados")
    print("Fim da atividade")
    sys.exit()

# cursor
cursor = db.cursor()

# funcao conectar.
def on_connect(client, userdata, flags, rc):
    print("Conectado com o codigo: "+str(rc))

    # inscrito neste topico
    client.subscribe(topic)


def on_message(client, userdata, msg):

    print(msg.topic+" "+str(msg.payload)+" "+time.asctime())

    #diz onde vai cada dado  no banco de dados nas tabelas corretas. (anotar sintaxe pois e muito confusa)
    if msg.topic[6:9] == "lum":
        sql = """INSERT INTO `luminosidade` (`id_dado`, `dado`, `dataHoraDado`) VALUES (NULL, '""" + str(msg.payload)+ """',+ NULL);"""
    if msg.topic[6:9] == "umi":
        sql = """INSERT INTO `umidade` (`id_dado`, `dado`, `dataHoraDado`) VALUES (NULL, '""" + str(msg.payload)+ """',+ NULL);"""
    if msg.topic[6:9] == "tem":
        sql = """INSERT INTO `temperatura` (`id_dado`, `dado`, `dataHoraDado`) VALUES (NULL, '""" + str(msg.payload)+ """',+ NULL);"""


    try:
        #envia para o banco
        cursor.execute(sql)
        db.commit()
    except:
        db.rollback()
        print("Nao foi possivel armazenar no banco")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

try:
    client.connect(br_adress, br_port, br_keep)
except:
    print("Nao foi possivel conectar ao MQTT")
    print("Encerrando atividade")
    db.close()
    sys.exit()


try:
        # continue rodando, ou saia atraves de crtl+C
    client.loop_forever()
except KeyboardInterrupt:
    print("Fim da execucao")
    db.close()
