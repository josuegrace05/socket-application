#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringListModel>
#include "ui_chat2.h"

class Client : public QWidget, private Ui::chat2
{
    Q_OBJECT

public:
    Client();
private slots:
        void on_connetionButton_clicked();
        void on_disconnectButton_clicked();
        void on_boutonEnvoyer_clicked();
        void on_updateButton_clicked();
        void on_messageText_returnPressed();
        void on_usernameValue_returnPressed();
        void receivedData();
        void connected();
        void disconected();
        void errorSocket(QAbstractSocket::SocketError erreur);

    private:
        QTcpSocket *socket; // Represent the server
        QString m_username;
        quint16 m_messageSize;
};

#endif // CLIENT_H
