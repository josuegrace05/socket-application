#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* id, QString ip, QString username = "Usuario", QWidget *parent = nullptr);
    ~Client();
    void addPlaylist(QList <QString> playlist);
    void addUsername(QString username);
    QString username();
    QString ipAddress();
    QString port();
    QTcpSocket *id();

signals:

public slots:

private :

    QString m_username;
    QList <QString> m_playlist;
    QString m_ip;
    QTcpSocket* m_id;
};

#endif // CLIENT_H
