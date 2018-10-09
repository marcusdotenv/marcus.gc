# Soluções para possíveis problemas

1. Problemas em instalar o MySQL e em utilizar o phpmyadmin no RaspberryPi;

O MySQL foi substituído no Raspbian 9 pelo MariaDB.

Se você instalar o pacote *mysql-server* ele vai estar instalando o *mariadb-client mariadb-server*.
Não sentiu que faltou algo nessa instalação?
Sim! No MySQL você definia uma senha para para o usuário root do mysql na instalação, com o MariaDB isso não acontece pois ele vem sem senha de root!
Como usuário root não tem senha você não vai conseguir logar com ele no PHPMyAdmin.

Portanto, utilize os seguintes comandos para alterar a senha do root no MariaDB:

> sudo mysql -uroot -p

Dê enter quando pedir senha, afinal está sem. Dentro do ambiente do MariaDB, faça:

> USE mysql;

> UPDATE user SET password=PASSWORD('digitesenha') WHERE User='root';

> UPDATE user SET plugin="mysql_native_password";

> FLUSH PRIVILEGES;

>quit;

Pronto.

http://forum.fazedores.com/t/mysql-no-raspbian-sem-acesso-e-nao-pede-senha-na-instalacao/4760/6



2. Instalar o driver do ESP8266, para utilizá-lo na IDE do arduino

O ESP8266 na placa WemosD1 precisa de um driver para operar na porta USB. Para tanto, é unânime que se recomenda a utilização do conversor USB-Serial CH340G(V3).


Clique [aqui](https://wiki.wemos.cc/_media/file:ch341ser_win.zip) para fazer o download do driver.

Uma vez baixado, execute o arquivo como administrador e proceda normalmente para instalar. 
