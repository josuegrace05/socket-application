#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

//Definiton of a client conected in the server
class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* id, QString ip, QString username = "Usuario", QWidget *parent = nullptr);
    ~Client();

    void addUsername(QString username);
    QString username();
    QString ipAddress();
    QString port();
    QTcpSocket *id();

signals:

public slots:

private :

    //Client atributes
    QString m_username;
    QString m_ip;
    QTcpSocket* m_id;
};

#endif // CLIENT_H
