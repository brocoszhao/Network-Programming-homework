//mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "client.h"
#include <QColorDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket();

    srv=new Server(this);
    //connect(srv,SIGNAL(sndFileName(QString),this,SLOT(getFileName(QString)));

    //连接信号槽
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);
    QObject::connect(ui->textEdit_Send,SIGNAL(currentCharFormatChanged(QTextCharFormat)),
                     this,SLOT(curFmtChanged(const QTextCharFormat)));

    ui->pushButton_Send->setEnabled(false);
    ui->lineEdit_IP->setText("127.0.0.1");
    ui->lineEdit_Port->setText("8765");

}

MainWindow::~MainWindow()
{
    delete this->socket;
    delete ui;
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if(ui->pushButton_Connect->text() == tr("连接"))
    {
        QString IP;
        int port;

        //获取IP地址
        IP = ui->lineEdit_IP->text();
        //获取端口号
        port = ui->lineEdit_Port->text().toInt();

        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost(IP, port);

        //等待连接成功
        if(!socket->waitForConnected(30000))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";

        //发送按键使能
        ui->pushButton_Send->setEnabled(true);
        //修改按键文字
        ui->pushButton_Connect->setText("断开连接");
    }
    else
    {
        //断开连接
        socket->disconnectFromHost();
        //修改按键文字
        ui->pushButton_Connect->setText("连接");
        ui->pushButton_Send->setEnabled(false);
    }
}

void MainWindow::on_pushButton_Send_clicked()
{
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
     //获取文本框内容并以ASCII码形式发送
    socket->write(ui->textEdit_Send->toPlainText().toUtf8());
    socket->flush();
}

void MainWindow::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->textEdit_Recv->toPlainText();
        str+=tr(buffer)+"\n";
        //刷新显示
        ui->textEdit_Recv->setText(str);
    }
}

void MainWindow::socket_Disconnected()
{
    //发送按键失能
    ui->pushButton_Send->setEnabled(false);
    //修改按键文字
    ui->pushButton_Connect->setText("连接");
    qDebug() << "Disconnected!";
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
   ui->textEdit_Send->setCurrentFont(f);
   ui->textEdit_Send->setFocus();
   ui->textEdit_Recv->setCurrentFont(f);
   ui->textEdit_Recv->setFocus();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->textEdit_Send->setFontPointSize(arg1.toDouble());
    ui->textEdit_Send->setFocus();
    ui->textEdit_Recv->setFontPointSize(arg1.toDouble());
    ui->textEdit_Recv->setFocus();
}

void MainWindow::on_toolButton_2_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit_Send->setFontWeight(QFont::Bold);
        ui->textEdit_Recv->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit_Send->setFontWeight(QFont::Normal);
        ui->textEdit_Recv->setFontWeight(QFont::Normal);
    }
    ui->textEdit_Send->setFocus();
    ui->textEdit_Recv->setFocus();
}

void MainWindow::on_toolButton_3_clicked(bool checked)
{
    ui->textEdit_Send->setFontItalic(checked);
    ui->textEdit_Recv->setFontItalic(checked);
    ui->textEdit_Send->setFocus();
    ui->textEdit_Recv->setFocus();
}

void MainWindow::on_toolButton_clicked()
{
    color=QColorDialog::getColor(color,this);
    if(color.isValid()){
        ui->textEdit_Send->setTextColor(color);
        ui->textEdit_Recv->setTextColor(color);
        ui->textEdit_Send->setFocus();
        ui->textEdit_Recv->setFocus();
    }
}

void MainWindow::curFmtChanged(const QTextCharFormat &fmt)
{
    ui->fontComboBox->setCurrentFont(fmt.font());
    if(fmt.fontPointSize()<8){
        ui->comboBox->setCurrentIndex(1);
    }
    else
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(QString::
                                                           number(fmt.fontPointSize())));
    }
    ui->toolButton_2->setChecked(fmt.font().bold());
    ui->toolButton_3->setChecked(fmt.font().italic());
    color=fmt.foreground().color();

}

/*
void MainWindow::getFileName(QString name)
{
    fileName=name;
    sndMsg(FileName);
}


void MainWindow::on_toolButton_4_clicked()
{
    srv->show();
    srv->initSrv();
}
*/
