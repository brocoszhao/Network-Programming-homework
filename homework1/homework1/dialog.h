#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QtNetWork>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0,Qt::WindowFlags f=0);
    ~Dialog();
public slots:
    void newConnection();
    void readclient();

private:
   QLabel *InfoLabel;
   QListWidget *ContentListWidget;
   QLabel *PortLabel;
   QLineEdit *PortLineEdit;
   QPushButton *StartButton;
   QGridLayout *mainLayout;
   QTcpSocket *Server;
   QTcpSocket *clientConnection;
   QTcpServer *server;
};

#endif // DIALOG_H
