#include "client.h"

Client::Client()
{
    setupUi(this);

        socket = new QTcpSocket(this);
        m_playlistModel = new QStringListModel;
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
    out << QString("connected");
    out.device()->seek(0);
    out << (quint16) (cmd.size() - sizeof(quint16));
    socket->write(cmd);
}
// Sending a chat message
void Client::on_boutonEnvoyer_clicked()
{
    QByteArray chat;
    QDataStream out(&chat, QIODevice::WriteOnly);

    // Preparing the mensagem to be sent

    if(userIp->text().isEmpty())
    {
        QMessageBox::critical(this,"Erro","Precisa indentificar o endereco ip do destinatario");
        return;
    }

    QString message = "chat:"+ userIp->text() + ":" + tr("<strong>") + m_username + tr("</strong> : ") + messageText->text();

    if(message.contains("!quero",Qt::CaseSensitive))
        m_wantedMusic = message.split(',',QString::SkipEmptyParts);

    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));

    socket->write(chat); // We send the chat.

    messageText->clear(); // We clear the messageBoxText
    messageText->setFocus(); // We get back the cursor in
}
// Appuyer sur la touche Entrée a le même effet que cliquer sur le bouton "Envoyer"
void Client::on_ShareMusicButton_clicked()
{

        QItemSelectionModel *selectedMusics = playlist->selectionModel();
        QModelIndexList selectionList = selectedMusics->selectedIndexes();
        QString musicsTobeShared;

        QList<QString> musics;

        for (int i = 0 ; i < selectionList.size() ; i++)
        {
            QVariant selectedMusic = m_playlistModel->data(selectionList[i], Qt::DisplayRole);
            musicsTobeShared = selectedMusic.toString();
            QFile file(m_musicDiretory+"/"+musicsTobeShared);

            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file);
                QString line = in.readAll();
                line += ";";
                musics << line;
                file.close();
            }

            else
                QMessageBox(this,"Erro","Não conseguiu abrir o arquivo de musica");
        }

        QByteArray package;
        QDataStream out(&package,QIODevice::WriteOnly);
        QString cmd("musics:");
        cmd += userIp->text()+":";

        for(int i = 0; i < musics.size(); i++)
            cmd += musics[i];

        out << (quint16)0;
        out << cmd;
        out.device()->seek(0);
        out << (quint16) (package.size() - sizeof(quint16));

        socket->write(package);
        listeMessages->append("Musicas compartilhadas com successo");

}
void Client::on_folderButton_clicked()
{
   QString musicFolder = QFileDialog::getExistingDirectory(this);
   m_musicDiretory = musicFolder;

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
   m_playlistModel->setStringList(QStringList(list));
   playlist->setModel(m_playlistModel);
   playlist->setSelectionMode(QAbstractItemView::ExtendedSelection);
}
void Client::on_sharePlaylistButton_clicked()
{
    QStringList musics = m_playlistModel->stringList();

    if(musics.isEmpty())
    {
        QMessageBox::critical(this,"Erro","A sua playlist esta vazia. Selecione primeiro uma playlist.");
        return;
    }

    if(userIp->text().isEmpty())
     {
        QMessageBox::critical(this,"Erro","Por favor define o IP do usuario com quem quer compartilhar.");
        return;
     }

    QByteArray package;
    QDataStream out(&package,QIODevice::WriteOnly);
    QString cmd("playlist:");
    cmd += userIp->text() + ":<br>";

    out << (quint16)0;

    for(int i = 0; i < musics.size(); i++)
        cmd += musics[i] + "<br>";

    out << cmd;
    out.device()->seek(0);
    out << (quint16) (package.size() - sizeof(quint16));

    socket->write(package);
    listeMessages->append("<em>Playlist mandado com sucesso!</em>");

}
void Client::on_messageText_returnPressed()
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

    if(messageRecu.contains("musics"))
    {
        for(int i = 0; i < m_wantedMusic.size(); i++)
        {
            QFile file(m_musicDiretory+"/"+m_wantedMusic[i]);

            if(file.open(QIODevice::WriteOnly))
            {
                QTextStream out(&file);
                out << messageRecu.section(';',i,i);
            }

            file.close();
        }
    }

    // On affiche le message sur la zone de Chat
    listeMessages->append(messageRecu);

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}
// Ce slot est appelé lorsque la connexion au serveur a réussi
void Client::connecte()
{
    m_username = usernameValue->text();
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
    listeMessages->append(tr("<em>Desconectado do servidor</em>"));
}
// Ce slot est appelé lorsqu'il y a une erreur
void Client::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            listeMessages->append(tr("<em>ERRO : O servidor não foi encontrado. Verifique o IP e a porta.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            listeMessages->append(tr("<em>ERRO : O servidor recusou a conexao. Verificar se o programa \"servidor\" não foi bem executado. Verfique tambem o IP e a porta.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            listeMessages->append(tr("<em>ERRO : O servidor cortou a conexao.</em>"));
            break;
        default:
            listeMessages->append(tr("<em>ERRO : ") + socket->errorString() + tr("</em>"));
    }

    boutonConnexion->setEnabled(true);
}
