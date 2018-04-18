//mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include<QColorDialog>
#include<QTextCharFormat>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

    void server_New_Connect();

    void socket_Read_Data();

    void socket_Disconnected();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_toolButton_2_clicked(bool checked);

    void on_toolButton_clicked(bool checked);

    void on_toolButton_3_clicked();

    void curFmtChanged(const QTextCharFormat &fmt);

private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    QTcpSocket* socket;
    QColor color;
};

#endif // MAINWINDOW_H
