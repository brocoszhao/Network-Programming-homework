/********************************************************************************
** Form generated from reading UI file 'plotdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDIALOG_H
#define UI_PLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_plotdialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *widget;

    void setupUi(QDialog *plotdialog)
    {
        if (plotdialog->objectName().isEmpty())
            plotdialog->setObjectName(QStringLiteral("plotdialog"));
        plotdialog->resize(400, 300);
        horizontalLayoutWidget = new QWidget(plotdialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(29, 29, 341, 251));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QCustomPlot(horizontalLayoutWidget);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(plotdialog);

        QMetaObject::connectSlotsByName(plotdialog);
    } // setupUi

    void retranslateUi(QDialog *plotdialog)
    {
        plotdialog->setWindowTitle(QApplication::translate("plotdialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class plotdialog: public Ui_plotdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDIALOG_H
