/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpServer
{
public:
    QLabel *serverStatusLabel;
    QProgressBar *progressBar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *serverOpenBtn;
    QPushButton *serverSendBtn;
    QPushButton *serverCloseBtn;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName(QStringLiteral("TcpServer"));
        TcpServer->resize(450, 200);
        TcpServer->setMinimumSize(QSize(450, 200));
        TcpServer->setMaximumSize(QSize(450, 200));
        TcpServer->setLayoutDirection(Qt::LeftToRight);
        serverStatusLabel = new QLabel(TcpServer);
        serverStatusLabel->setObjectName(QStringLiteral("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(12, 10, 391, 70));
        QFont font;
        font.setPointSize(12);
        serverStatusLabel->setFont(font);
        progressBar = new QProgressBar(TcpServer);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 100, 350, 20));
        progressBar->setMinimumSize(QSize(320, 20));
        progressBar->setMaximumSize(QSize(320, 20));
        progressBar->setValue(0);
        widget = new QWidget(TcpServer);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 137, 254, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        serverOpenBtn = new QPushButton(widget);
        serverOpenBtn->setObjectName(QStringLiteral("serverOpenBtn"));
        serverOpenBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(serverOpenBtn);

        serverSendBtn = new QPushButton(widget);
        serverSendBtn->setObjectName(QStringLiteral("serverSendBtn"));
        serverSendBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(serverSendBtn);

        serverCloseBtn = new QPushButton(widget);
        serverCloseBtn->setObjectName(QStringLiteral("serverCloseBtn"));
        serverCloseBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(serverCloseBtn);


        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QApplication::translate("TcpServer", "\345\217\221\351\200\201\346\226\271", Q_NULLPTR));
        serverStatusLabel->setText(QApplication::translate("TcpServer", "\350\257\267\351\200\211\346\213\251\350\246\201\345\217\221\351\200\201\347\232\204\346\226\207\344\273\266", Q_NULLPTR));
        serverOpenBtn->setText(QApplication::translate("TcpServer", "\346\211\223\345\274\200", Q_NULLPTR));
        serverSendBtn->setText(QApplication::translate("TcpServer", "\345\217\221\351\200\201", Q_NULLPTR));
        serverCloseBtn->setText(QApplication::translate("TcpServer", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
