#include "server.h"

Server::Server()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_exit = new QPushButton(tr("Quitter"));
    m_info = new QLabel;
    layout->addWidget(m_info);
    layout->addWidget(m_exit);
    setLayout(layout);

    setWindowTitle(tr("ZeroChat - Serveur"));

    m_server = new QTcpServer(this);
    if(!m_server->listen(QHostAddress::Any, 50885))// Démarrage du serveur sur toutes les IP disponibles et sur le port 50585
    {
        //if not started correctly
        m_info->setText(tr("Le serveur na pas pu demare. "
                           "Raison: <br />") + m_server->errorString());
    }

    else
    {
        //if started correctly
        m_info->setText(tr("Le serveur a ete demarre sur le port <strong>") +
                        QString::number(m_server->serverPort())
                        + tr("</strong>.<br />Des clients peuvent maintenant se connecter."));
        connect(m_server,SIGNAL(newConnection()),this,SLOT(newConection()));

    }

    m_messSize = 0;
    connect(m_exit,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
}

void Server::newConection()
{

    QTcpSocket *newClient = m_server->nextPendingConnection();//Get the address of the client connected

    QString clientInfos = QString("<strong> New Client:</strong><br>IP Address: %1. Port: %2").arg(newClient->peerAddress().toString()).arg(newClient->peerPort());
    sendToAll(clientInfos);

    m_clients << newClient;

    connect(newClient,SIGNAL(readyRead()),this, SLOT(receivedData()));//Signal emited when a client has sent a message
    connect(newClient, SIGNAL(disconnected()), this, SLOT(disconectClient()));//Signal emited when a client disconnected
}
void Server::receivedData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
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

    sendToAll(message);//send it to every body
    m_messSize = 0; //get back the message size to zero to receive messages of others clientes.
}
void Server::disconectClient()
{
    sendToAll(tr("<em>Un client vient de se deconnecter</em>"));
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    //determined who disconected
    if(socket == 0)//the object was not a TcpSocket
        return;

    m_clients.removeOne(socket);
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
        m_clients[i]->write(package);


}
