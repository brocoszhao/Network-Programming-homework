//mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QTcpSocket>

class Server;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void hasPendingFile(QString usrname,QString srvaddr,QString clntaddr,QString filename);

private slots:

    void on_pushButton_Connect_clicked();

    void on_pushButton_Send_clicked();

    void socket_Read_Data();

    void socket_Disconnected();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_toolButton_2_clicked(bool checked);

    void on_toolButton_3_clicked(bool checked);

    void on_toolButton_clicked();

    void curFmtChanged(const QTextCharFormat &fmt);

    void getFileName(QString);

    void on_toolButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QColor color;

    QString fileName;
    Server *srv;
};

#endif // MAINWINDOW_H
