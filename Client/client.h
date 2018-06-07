#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtNetwork>
#include "ui_chat2.h"

class Client : public QWidget, private Ui::chat2
{
    Q_OBJECT

public:
    Client();
private slots:
        void on_boutonConnexion_clicked();
        void on_boutonEnvoyer_clicked();
        void on_message_returnPressed();
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);

    private:
        QTcpSocket *socket; // Représente le serveur
        quint16 tailleMessage;
};

#endif // CLIENT_H
