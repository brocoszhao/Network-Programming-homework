#include "plotdialog.h"
#include "ui_plotdialog.h"
#include "qcustomplot.h"
#include "QFont"

plotdialog::plotdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotdialog)
{
    ui->setupUi(this);
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    plot =CreateAndInitPlotGraph(QString("Time(s)"),0,1200,QString("PS_POWER(KW)"),-1000,3000,QRect(0,0,800,475));
    mainLayout->addWidget(plot);
}

plotdialog::~plotdialog()
{
    delete ui;
}

QCustomPlot* plotdialog::CreateAndInitPlotGraph(QString xLabel,int xRangeL,int xRangeR,QString yLabel,int yRangeL,int yRangeR,QRect rect)
{
    QCustomPlot *customPlot = new QCustomPlot();
    customPlot->legend->setVisible(true);
    QFont lengendFont = font();
    lengendFont.setPointSize(9);
    customPlot->legend->setFont(lengendFont);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
    customPlot->setGeometry(rect);
    customPlot->xAxis->setLabel(xLabel);
    customPlot->xAxis->setRange(xRangeL,xRangeR);
    customPlot->yAxis->setLabel(yLabel);
    customPlot->yAxis->setRange(yRangeL,yRangeR);
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(QColor(Qt::black)));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsStepLeft);// li san de dian

    return customPlot;
}
