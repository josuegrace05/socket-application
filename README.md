# Obejtivo  
  Esse programa tem por objetivo mostrar o funcionamento do socket via uma applicação.
### Applicação implementada
Implementamos uma interface de chat entre vários clientes conectados ao um mesmo servidor. 
### Funcionamento
O usuário para se conectar precisa especificar seu username, o endereço ip do servidor e a porta na qual ela foi ligada. pode ser utilisada o botão `conectar` ou a tecla `enter`. 
Tendo uma conexão estabelecida, o usuário pode vizualizar a partir do botão `conectados` todos os usuarios conectados na rede inclusive ele mesmo. O botão `conectados` lista na janela de log o username e o endereço ip de quem está conectado.

Para se desconectar, basta clicar no botão `desconectar`. Ao se desconectar, o servidor manda uma mensagem para todo mundo notificando que um usuário se desconectou.

Para mandar uma mensagem para um outro usuaŕio, é preciso especificar o endereço ip do usuário destinatário. Feito isso, o usuário pode digitar sua mensagem e clicar no botão `mandar` ou simplesmente apertar `enter`.
### Compilar e executar o programa
Para executar o programa, é preciso installar alguns pacotes no terminal do linux digitando os com os seguintes comandos:

> sudo apt-get update

> sudo apt-get install qt4-dev-tools

> sudo apt-get install qtcreator

Feito isso, é preciso compliar os programas sevidor e cliente separadamente.
* Para executar o progama servidor:
  * Entrar na pasta `Server`
  * Executar:
  > qmake Chat.pro
  
  * Um Makefile será criado. Execute-o.
  > Makefile
  
  * O arquivo binário do programa será criado. Execute:
  > ./Chat
  
  * O programa servidor será lançado.
* Para executar o programa cliente
Entrar na pasta cliente e repetir o mesmo processo substituindo Chat por Chat2.
