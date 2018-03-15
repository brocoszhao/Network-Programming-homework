#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QDialog>
#include <QObject>

class TcpClientSocket:public QDialog
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent=0);

signals:
    void updateClients(QString,int);
    void disconnected(int);

protected slots:
    void slotDisconnected();
};
#endif // TCPCLIENTSOCKET_H
