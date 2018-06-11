#include "client.h"

//This method is the constructor of the client object
Client::Client()
{
    setupUi(this);
    disconnectButton->setEnabled(false);

    //instanciate client atributes
        socket = new QTcpSocket(this);

        connect(socket, SIGNAL(readyRead()), this, SLOT(receivedData()));
        connect(socket, SIGNAL(connected()), this, SLOT(connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconected()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));

        m_messageSize = 0;//initialize the size message to zero
}

// This method manage what happens when the client connect to the sever
void Client::on_connetionButton_clicked()
{
    //Show on the GUI that we are connecting
    logText->append(tr("<em>Tentativa de connexao...</em>"));

    if(usernameValue->text().isEmpty())//The username cannot be empty
    {
        QMessageBox::critical(this,"Erro","Username vazio");
        return;
    }

    connetionButton->setEnabled(false);
    disconnectButton->setEnabled(true);
    socket->connectToHost(serveurIP->text(), serveurPort->value()); // We connect on the server specified
}
//List all clients connected requisition
void Client::on_updateButton_clicked()
{
    //This method create the requisition to list all clients connected.
    QByteArray cmd;//Create the package we will send
    QDataStream out(&cmd, QIODevice::WriteOnly);//We a stream which will be used to write on the package
    out << (quint16) 0; //We write 0 at the begining of the pacakage to the reserve the message size
    out << QString("connected");//We write the requisition tag
    out.device()->seek(0);//We put the stream pointer at the begining
    out << (quint16) (cmd.size() - sizeof(quint16));//We write the message size
    socket->write(cmd);//we send the package
}
// Sending a chat message
void Client::on_boutonEnvoyer_clicked()
{
    QByteArray chat;
    QDataStream out(&chat, QIODevice::WriteOnly);

    // Preparing the message to be send

    if(userIp->text().isEmpty())//Must specify the client destinator ipaddress
    {
        QMessageBox::critical(this,"Erro","Precisa indentificar o endereco ip do destinatario");
        return;
    }

    //We mount the message to be send
    QString message = "chat:"+ userIp->text() + ":" + tr("<strong>") + m_username + tr("</strong> : ") + messageText->text();


    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));

    socket->write(chat); // We send the chat.

    messageText->clear(); // We clear the messageBoxText
    messageText->setFocus(); // We get back the cursor in
}

void Client::on_messageText_returnPressed()
{
   this->on_boutonEnvoyer_clicked();
}
void Client::on_usernameValue_returnPressed()
{
    this->on_connetionButton_clicked();
}
// We the client receive data
void Client::receivedData()
{
    /* The logic her is the same writen in the server class
    */
    QDataStream in(socket);

    if (m_messageSize == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> m_messageSize;
    }

    if (socket->bytesAvailable() < m_messageSize)
        return;

    QString receivedMessage;
    in >> receivedMessage;


    // We show the message on the chat area
    if(receivedMessage.contains("@"))
        logText->append(receivedMessage);
    else
        listMessages->append(receivedMessage);

    m_messageSize = 0;
}
// This slot method is called when the conection to the server was successfull
void Client::connected()
{
    //We conected sucessfully to the sever.Now we will going to update the username.
    m_username = usernameValue->text();
    logText->append(tr("<em>Connectado com successo !</em>"));

    //We got the username, now we will send it to the server
    QByteArray username;
    QDataStream out(&username, QIODevice::WriteOnly);
    QString aux("username:");//We put the tag for this requisition
    out << (quint16) 0;
    out << aux + usernameValue->text();
    out.device()->seek(0);
    out << (quint16) (username.size() - sizeof(quint16));

    socket->write(username);
}
void Client::on_disconnectButton_clicked()
{
    socket->abort(); // We abort the client conection from the server
}
//This slot method is called when the client disconect from the server
void Client::disconected()
{
    logText->append(tr("<em>Desconectado do servidor</em>"));
    disconnectButton->setEnabled(false);
    connetionButton->setEnabled(true);
}
// This slot method is called when occur an erro with the conection to the server
void Client::errorSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // We inform what was the erro
    {
        case QAbstractSocket::HostNotFoundError:
            logText->append(tr("<em>ERRO : O servidor não foi encontrado. Verifique o IP e a porta.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            logText->append(tr("<em>ERRO : O servidor recusou a conexao. Verificar se o programa \"servidor\" não foi bem executado. Verfique tambem o IP e a porta.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            logText->append(tr("<em>ERRO : O servidor cortou a conexao.</em>"));
            break;
        default:
            logText->append(tr("<em>ERRO : ") + socket->errorString() + tr("</em>"));
    }

    connetionButton->setEnabled(true);
}
