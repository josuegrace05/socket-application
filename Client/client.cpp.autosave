#include "client.h"

Client::Client()
{
    setupUi(this);

        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
        connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

        tailleMessage = 0;
}

// Tentative de connexion au serveur
void Client::on_boutonConnexion_clicked()
{
    //Show on the GUI that we are connecting
    listeMessages->append(tr("<em>Tentativa de connexao...</em>"));
    if(usernameValue->text().isEmpty())
    {
        QMessageBox::critical(this,"Erro","Username vazio");
        return;
    }

    boutonConnexion->setEnabled(false);
    socket->abort(); // We abort previous conexions if they exist
    socket->connectToHost(serveurIP->text(), serveurPort->value()); // We connect on the server specified
}
//List all clients connected requisition
void Client::on_updateButton_clicked()
{
    QByteArray cmd;
    QDataStream out(&cmd, QIODevice::WriteOnly);
    out << (quint16) 0;
    out << QString("list");
    out.device()->seek(0);
    out << (quint16) (cmd.size() - sizeof(quint16));
    socket->write(cmd);
}
// Envoi d'un message au serveur
void Client::on_boutonEnvoyer_clicked()
{
    QByteArray playlist;
    QDataStream out(&playlist, QIODevice::WriteOnly);

    // Preparing the playlist to be sent
    QDir dir("../myMusic");
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    QFileInfoList allMusic = dir.entryInfoList();

    //QString messageAEnvoyer = tr("<strong>") + pseudo->text() +tr("</strong> : ") + playlist->;
    QString musicsNames = tr("<strong>") + pseudo->text() + " playlist:\n" + tr("</strong><br>");
    for (int i = 0; i < allMusic.size(); i++)
    {
        QFileInfo musicInfo = allMusic.at(i);
        musicsNames += QString("%1 ").arg(musicInfo.fileName());
        musicsNames += "<br>";
    }
    out << (quint16) 0;
    out << musicsNames;
    out.device()->seek(0);
    out << (quint16) (playlist.size() - sizeof(quint16));

    socket->write(playlist); // On envoie le paquet

    message->clear(); // On vide la zone d'écriture du message
    message->setFocus(); // Et on remet le curseur à l'intérieur
}
// Appuyer sur la touche Entrée a le même effet que cliquer sur le bouton "Envoyer"
void Client::on_folderButton_clicked()
{
   QString musicFolder = QFileDialog::getExistingDirectory(this);

   QDir dir(musicFolder);
   dir.setFilter(QDir::Files);
   dir.setSorting(QDir::Name);
   QFileInfoList allMusic = dir.entryInfoList();

   //QString messageAEnvoyer = tr("<strong>") + pseudo->text() +tr("</strong> : ") + playlist->;
   //QString musicsNames = tr("<strong>")+" playlist:"+tr("</strong><br>");
   QStringList list;
   for (int i = 0; i < allMusic.size(); i++)
   {
       QFileInfo musicInfo = allMusic.at(i);
       list << QString("%1").arg(musicInfo.fileName());
   }

   //list << musicsNames;
   QStringListModel *model = new QStringListModel(QStringList(list));
   playlist->setModel(model);
   playlist->setSelectionMode(QAbstractItemView::ExtendedSelection);
}
void Client::on_message_returnPressed()
{
   this->on_boutonEnvoyer_clicked();
}
void Client::on_usernameValue_returnPressed()
{
    this->on_boutonConnexion_clicked();
}
// On a reçu un paquet (ou un sous-paquet)
void Client::donneesRecues()
{
    /* Même principe que lorsque le serveur reçoit un paquet :
    On essaie de récupérer la taille du message
    Une fois qu'on l'a, on attend d'avoir reçu le message entier (en se basant sur la taille annoncée tailleMessage)
    */
    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;


    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    // On affiche le message sur la zone de Chat
    listeMessages->append(messageRecu);

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}
// Ce slot est appelé lorsque la connexion au serveur a réussi
void Client::connecte()
{
    listeMessages->append(tr("<em>Connectado com successo !</em>"));
    QByteArray username;
    QDataStream out(&username, QIODevice::WriteOnly);
    QString aux("username:");
    out << (quint16) 0;
    out << aux + usernameValue->text();
    out.device()->seek(0);
    out << (quint16) (username.size() - sizeof(quint16));

    socket->write(username);
    boutonConnexion->setEnabled(true);
}
// Ce slot est appelé lorsqu'on est déconnecté du serveur
void Client::deconnecte()
{
    listeMessages->append(tr("<em>Déconnecté du serveur</em>"));
}
// Ce slot est appelé lorsqu'il y a une erreur
void Client::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            listeMessages->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            listeMessages->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }

    boutonConnexion->setEnabled(true);
}
