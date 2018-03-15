#include "server.h"

Server::Server(QObject *parent,int port)
   :QDialog(parent)
{
    listen(QHostAddress::Any,port);
}

void Server::incomingConnection(int socketDescriptor())
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),
            this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,
            SLOT(slotDisconnected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor());
}


void Server::slotDisconnected(int descriptor)
{}
