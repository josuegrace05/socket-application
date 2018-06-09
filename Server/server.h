#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtNetwork>
#include <QMessageBox>
#include "client.h"

class Server : public QWidget
{
    Q_OBJECT

public:
    Server();
    void sendToAll(const QString &message);
    void sendToClient(QTcpSocket *id, const QString &message);

private slots:
    void newConection();
    void receivedData();
    void disconectClient();
    void updateUsername(QString username, QString ipAddress);
    Client* searchClient(QString ipAddress);

private:
    QPushButton *m_exit;
    QLabel *m_info;

    QTcpServer *m_server;
    QList <Client *> m_clients;
    quint16 m_messSize;
};

#endif // SERVER_H
