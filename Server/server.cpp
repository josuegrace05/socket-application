#include "server.h"

Server::Server()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_exit = new QPushButton(tr("Sair"));
    m_info = new QLabel;
    layout->addWidget(m_info);
    layout->addWidget(m_exit);
    setLayout(layout);

    setWindowTitle(tr("Xarefy"));

    m_server = new QTcpServer(this); //Created the Server with TCP procotol

    if(!m_server->listen(QHostAddress::Any, 50885))// Started the server on all the IP availables and on the port 50585
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

void Server::newConection()
{

    QTcpSocket *newClient = m_server->nextPendingConnection();//Get the address of the client connected
    Client *user = new Client(newClient,newClient->peerAddress().toString());
    m_clients << user;

    connect(newClient,SIGNAL(readyRead()),this, SLOT(receivedData()));//Signal emited when a client has sent a message
    connect(newClient, SIGNAL(disconnected()), this, SLOT(disconectClient()));//Signal emited when a client disconnected
}
void Server::updateUsername(QString username, QString ipAddress)
{

    QString tag("Usuario");

    for(int i = 0; i < m_clients.size(); i++)
        if(m_clients[i]->ipAddress() == ipAddress && m_clients[i]->username() == tag)
            m_clients[i]->addUsername(QString("%1%2").arg("@").arg(username));
}
Client* Server::searchClient(QString ipAddress)
{
    for(int i = 0; i < m_clients.size(); i++)
        if(m_clients[i]->ipAddress() == ipAddress)
            return m_clients[i];
    return NULL;
}

void Server::receivedData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    Client *peerId;
    Client *senderId;

    if(socket == 0)//we didnt recognize who sent the message
        return;
    //else get back the message

    QDataStream in(socket);

    if(m_messSize == 0)//we started receiving data.
    {
        if(socket->bytesAvailable() < (int)sizeof(quint16)) //We check if we have sufficient data to get the size of the message
            return; //we dont have the entirely mess yet
        in >> m_messSize; //the entirely message arrived, we get back his size
    }

    if(socket->bytesAvailable() < m_messSize) //We received enough data to know the size of the message. Now we wait until we received all the data
        return; // we stop here if we dont have all the message

    QString message; //here we have all the message. We get it.
    in >> message;

    if(message.contains("username",Qt::CaseInsensitive))
        updateUsername(message.section(':',1,1),socket->peerAddress().toString());

    else if(message.contains(("connected"),Qt::CaseSensitive))
    {
        QString list;
        for(int i = 0; i < m_clients.size(); i++)
             list += QString("<strong>%1</strong> IP: %2<br>").arg(m_clients[i]->username()).arg(m_clients[i]->ipAddress());
        sendToClient(socket,list);
    }

    else if(message.contains("playlist",Qt::CaseSensitive))
    {

        peerId = searchClient(message.section(':',1,1));
        senderId = searchClient(socket->peerAddress().toString());

        if(peerId != NULL)
            sendToClient(peerId->id(),QString("%1 playlist:<br>%2").arg(senderId->username()).arg(message.section(':',2)));
        else
            sendToClient(socket,QString("O <strong>%1</strong> nao esta conectado. Tente mais tarde<br>.").arg(peerId->username()));
    }

    else if(message.contains("chat"),Qt::CaseSensitive)
    {
        peerId = searchClient(message.section(':',1,1));

        if(peerId != NULL)
            sendToClient(peerId->id(),message.section(':',2));
        else
            sendToClient(socket,"O usuario requesitado nao se encitra conectado na rede.");
    }
    else if(message.contains("musics"),Qt::CaseSensitive)
    {
        peerId = searchClient(message.section(':',1,1));

        if(peerId != NULL)
            sendToClient(peerId->id(),"musics:"+ message.section(':',2));
        else
            sendToClient(socket,"O usuario requesitado nao se encitra conectado na rede.");
    }
    m_messSize = 0; //get back the message size to zero to receive messages of others clientes.
}
void Server::disconectClient()
{

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    //determined who disconected
    if(socket == 0)//the object was not a TcpSocket
        return;


    Client *deleteClient;
    for(int i = 0; i < m_clients.size(); i++)
        if(m_clients[i]->id() == socket)
            deleteClient = m_clients[i];

    sendToAll(QString("<em> O %1 se desconectou</em>").arg(deleteClient->username()));

    m_clients.removeOne(deleteClient);
    socket->deleteLater();//We cannot do delete Client bcz it will bug Qt. We just say to him to delete it later.

}
void Server::sendToAll(const QString &message)
{
    QByteArray package;
    QDataStream out(&package, QIODevice::WriteOnly);
    out << (quint16) 0;//we write 0 at the begining to keep the space to write the size
    out << message;//then we add the messsage
    out.device()->seek(0);//we postioned in the begining of the package
    out << (quint16)(package.size() - sizeof(quint16));//we delete the zero we keeped

    //send the package to all the clients conected to the server

    for(int i = 0; i < m_clients.size(); i++)
        m_clients[i]->id()->write(package);
}

void Server::sendToClient(QTcpSocket *id, const QString &message)
{
    QByteArray package;
    QDataStream out(&package, QIODevice::WriteOnly);

    out << (quint16) 0;//we write 0 at the begining to keep the space to write the size
    out << message;//then we add the messsage
    out.device()->seek(0);//we postioned in the begining of the package
    out << (quint16)(package.size() - sizeof(quint16));//we delete the zero we keeped

    //send the package to the client
    id->write(package);
}
