#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QObject>

#include "tcpclientsocket.h"

class Server : public QDialog
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=0);
    QList<TcpClientSocket*> TcpClientSocketList;
signals:
    void updateServer(QString,int);
public slots:
    void updateClients(QString,int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor());
};
#endif // SERVER_H
