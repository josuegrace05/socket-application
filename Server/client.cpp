#include "client.h"

Client::Client(QTcpSocket *id, QString ip, QString username, QWidget *parent) : QWidget(parent)
{
    m_id = id;
    m_ip = ip;
    m_username = username;
}
void Client::addPlaylist(QList<QString> playlist)
{
    m_playlist = playlist;
}
void Client::addUsername(QString username)
{
    m_username = username;
}
QString Client::username()
{
    return m_username;
}
QString Client::ipAddress()
{
    return m_ip;
}
QString Client::port()
{
    return QString().arg(m_id->peerPort());
}
QTcpSocket* Client::id()
{
    return m_id;
}

Client::~Client()
{

}
