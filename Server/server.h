#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtNetwork>
#include <QMessageBox>
#include "client.h"

//Definition of the server object
class Server : public QWidget
{
    Q_OBJECT

public:
    Server();
    void sendToAll(const QString &message);
    void sendToClient(QTcpSocket *id, const QString &message);
    void updateUsername(QString username, QString ipAddress);
    Client* searchClient(QString ipAddress);

private slots://Theses methods are called when his respecetived signal occur
    void newConection();
    void receivedData();
    void disconectClient();

private:
    QPushButton *m_exit;
    QLabel *m_info;
    QTcpServer *m_server;//The socket object of the server
    QList <Client *> m_clients;
    quint16 m_messSize;
};

#endif // SERVER_H
