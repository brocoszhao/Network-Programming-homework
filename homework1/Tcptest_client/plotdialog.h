#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include "QTableWidget"
#include "qcustomplot.h"
#include <QGridLayout>
#include "mainwindow.h"

#define XAXIS_BASE_RANGE (double)600

namespace Ui {
class plotdialog;
}

class plotdialog : public QDialog
{
    Q_OBJECT

public:
    explicit plotdialog(QWidget *parent = 0);
    ~plotdialog();

    QCustomPlot* CreateAndInitPlotGraph(QString xLabel,int xRangeL,int xRangeR,QString yLabel,int yRangeL,int yRangeR,QRect rect);
    void updateGraph(double point_x, double point_y);
    void processPlotXAxisExpand(double point_x);

private:
    Ui::plotdialog *ui;

    double m_plotXAxisThrehold;

    QHBoxLayout *mainLayout;
    QCustomPlot* plot;
};

#endif // PLOTDIALOG_H
