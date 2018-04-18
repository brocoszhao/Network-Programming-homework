#ifndef SERVER_H
#define SERVER_H
#include<QDialog>
#include<QTime>

class QFile;
class QTcpServer;
class QTcpSocket;


namespace Ui{
class Server;
}

class Server:public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent=0);
    ~Server();
    void initSrv();
    void refused();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Server *ui;
    qint16 tPort;
    QTcpServer *tSrv;
    QString fileName;
    QString theFileName;
    QFile *locFile;

    qint64 totalBytes;  //总共需要发哦送的字节数
    qint64 bytesWritten;  //已发送字节数
    qint64 bytesTobeWrite;  //待发送字节数
    qint64 payloadSize;   //被初始化为一个常量

    QByteArray outBlock; //缓存一次发送的数据

    QTcpSocket *clntConn;

    QTime time;

private slots:
    void sndMsg();
    void updClntProgress(qint64 numBytes);
    void on_sOpenBtn_clicked();

    void on_sSendBtn_clicked();

    void on_sCloseBtn_clicked();

signals:
    void sndFileName(QString fileName);
};
#endif // SERVER_H
