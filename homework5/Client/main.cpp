#include "tcpclient.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpClient w;
    w.setWindowTitle("Client");
    w.show();

    MainWindow h;
    h.show();
    h.hide();
    QObject::connect(&w,SIGNAL(showmainwindow()),&h,SLOT(receivelogin()));
    return a.exec();
}
