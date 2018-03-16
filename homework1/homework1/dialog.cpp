#include "dialog.h"
#include <QtNetWork>
#include <QDebug>

Dialog::Dialog(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("TCPServer"));

    InfoLabel = new QLabel(tr("信息:"));
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel(tr("端口:"));
    PortLineEdit= new QLineEdit;

    StartButton = new QPushButton(tr("创建连接"));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(InfoLabel,0,0);
    mainLayout->addWidget(ContentListWidget,1,0,1,3);
    mainLayout->addWidget(PortLabel,2,0);
    mainLayout->addWidget(PortLineEdit,2,1);
    mainLayout->addWidget(StartButton,2,2);

    connect(StartButton,SIGNAL(clicked()),this,SIGNAL(newConnection()));

}

Dialog::~Dialog()
{

}

void Dialog::newConnection()
{
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 6665);
    clientConnection = server->nextPendingConnection();
    connect(clientConnection,SIGNAL(readyRead()),this,SLOT(readclient()));
}

void Dialog::readclient()
{
    //QString str = clientConnection->readAll();
    char buf[1024];
    clientConnection->read(buf,1024);
}
