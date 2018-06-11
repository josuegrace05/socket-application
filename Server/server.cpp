#include "server.h"

Server::Server()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_exit = new QPushButton(tr("Sair"));
    m_info = new QLabel;
    layout->addWidget(m_info);
    layout->addWidget(m_exit);
    setLayout(layout);

    setWindowTitle(tr("XareChat"));

    m_server = new QTcpServer(this); //Create the Server with TCP procotol

    if(!m_server->listen(QHostAddress::Any, 50885))// Started the server on all the IP availables (local IP, Internet IP) and on the port 50585
    {
        //if not started correctly
        m_info->setText(tr("O servidor nao conseguiu ligar. "
                           "Motivo: <br />") + m_server->errorString());
    }

    else
    {
        //if started correctly
        m_info->setText(tr("O servidor ligou na porta <strong>") +
                        QString::number(m_server->serverPort())
                        + tr("</strong>.<br />Clientes agora podem se conectar."));
        connect(m_server,SIGNAL(newConnection()),this,SLOT(newConection()));

    }

    m_messSize = 0;
    connect(m_exit,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
}
//This method manage clientes conections to server and desconetions from the server.
void Server::newConection()
{

    QTcpSocket *newClient = m_server->nextPendingConnection(); //Get all informations about the socket of the client connected
    Client *user = new Client(newClient,newClient->peerAddress().toString()); //Based on theses informations, create a the client object.
    m_clients << user; //Add the new Client to the server client list

    connect(newClient,SIGNAL(readyRead()),this, SLOT(receivedData()));//Signal emited when a client has sent a message
    connect(newClient, SIGNAL(disconnected()), this, SLOT(disconectClient()));//Signal emited when a client disconnected
}
//This method is used to update the username of a new client connected
void Server::updateUsername(QString username, QString ipAddress)
{

    QString tag("Usuario");//This tag is used for identify the client requested case there is many clients with the same IP Address.

    for(int i = 0; i < m_clients.size(); i++) //Search the client requested
        if(m_clients[i]->ipAddress() == ipAddress && m_clients[i]->username() == tag)
            m_clients[i]->addUsername(QString("%1%2").arg("@").arg(username));//Update his username
}
//This method is used to search a client conected in the server
Client* Server::searchClient(QString ipAddress)
{
    for(int i = 0; i < m_clients.size(); i++)
        if(m_clients[i]->ipAddress() == ipAddress)
            return m_clients[i];
    return NULL;//The client is not conected to the server
}
//This method manage clients requisitions
void Server::receivedData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());//Identify the cleint who sent the requisition
    Client *peerId;

    if(socket == 0)//we didnt recognize who sent the message (requisition)
        return;
    //else get back the message

    QDataStream in(socket); //We are goint to read the data sent by the client

    if(m_messSize == 0)//if we have just started receiving the client data.
    {
        if(socket->bytesAvailable() < (int)sizeof(quint16)) //We get the size of the message which is an quint16 (this is an unsigned int with 16 bytes not depending on the arhcitecture of the computer
            return; //we dont have the entirely mess yet
        in >> m_messSize; //we read the entirely message size arrived.
    }

    if(socket->bytesAvailable() < m_messSize) //We received enough data to know the size of the message. Now we wait until we received all the data
        return; // we stop here if we dont have all the message

    QString message; //here we have all the message. We get it.
    in >> message;

    //Managing requisitions

    //If the client is connecting now, we have to update his username
    if(message.contains("username",Qt::CaseInsensitive))
        updateUsername(message.section(':',1,1),socket->peerAddress().toString());

    //If the client want to know which clients are connected in the server
    else if(message.contains(("connected"),Qt::CaseSensitive))
    {
        QString list;
        for(int i = 0; i < m_clients.size(); i++)//Fill the list of all clients conected
             list += QString("<strong>%1</strong> IP: %2<br>").arg(m_clients[i]->username()).arg(m_clients[i]->ipAddress());
        sendToClient(socket,list);//Give back the answer to client
    }

    //If the client is sending a message to another client
    else if(message.contains("chat"),Qt::CaseSensitive)
    {
        peerId = searchClient(message.section(':',1,1)); //We identify who is the client destinator

        if(peerId != NULL) //If we successly found the client destinator
            sendToClient(peerId->id(),message.section(':',2));//We send to him the message
        else//We did not identify the client destinator. Probably because he is not conected.
            sendToClient(socket,"O usuario requesitado nao se encontra conectado na rede.");
    }

    m_messSize = 0; //get back the message size to zero to receive new messages.
}
//This method manage clients desconecions
void Server::disconectClient()
{

    //If a client disconected from the server, this slot is called.

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    //determined who disconected

    if(socket == 0)//the object was not a TcpSocket which means we did not recognize who client disconected.
        return;

    Client *deleteClient;//We remove the client from the server client list
    for(int i = 0; i < m_clients.size(); i++)
        if(m_clients[i]->id() == socket)
            deleteClient = m_clients[i];

    sendToAll(QString("<em> O %1 se desconectou</em>").arg(deleteClient->username()));//We notify everybody that this client disconected.

    m_clients.removeOne(deleteClient);//Remove him from the list.
    socket->deleteLater();//We cannot do delete Client bcz it will bug Qt. We just say to him to delete it later.

}
//This method send a message to everyone conected to the server
void Server::sendToAll(const QString &message)
{
    QByteArray package;//We mount the package to be send
    QDataStream out(&package, QIODevice::WriteOnly);//We say that we will write on this package
    out << (quint16) 0;//we write 0 at the begining to keep the space to write the message size
    out << message;//then we add the messsage
    out.device()->seek(0);//we postioned the stream pinter pointer in the begining of the package
    out << (quint16)(package.size() - sizeof(quint16));//we replace the zero we keeped with the message size

    //send the package to all the clients conected to the server

    for(int i = 0; i < m_clients.size(); i++)//Send to everyone
        m_clients[i]->id()->write(package);
}
//This method send a message to a specific client
void Server::sendToClient(QTcpSocket *id, const QString &message)
{
    //This method is similar with the method above
    QByteArray package;
    QDataStream out(&package, QIODevice::WriteOnly);

    out << (quint16) 0;//we write 0 at the begining to keep the space to write the size
    out << message;//then we add the messsage
    out.device()->seek(0);//we postioned in the begining of the package
    out << (quint16)(package.size() - sizeof(quint16));//we delete the zero we keeped

    //send the package to the client
    id->write(package);
}
