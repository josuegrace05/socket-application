#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtNetwork>

class Server : public QWidget
{
    Q_OBJECT

public:
    Server();
    void sendToAll(const QString &message);

private slots:
    void newConection();
    void receivedData();
    void disconectClient();

private:
    QPushButton *m_exit;
    QLabel *m_info;

    QTcpServer *m_server;
    QList <QTcpSocket *> m_clients;
    quint16 m_messSize;
};

#endif // SERVER_H
