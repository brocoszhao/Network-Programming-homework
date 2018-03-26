#include "plotdialog.h"
#include "ui_plotdialog.h"
#include "qcustomplot.h"
#include "QFont"

plotdialog::plotdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotdialog)
{
    ui->setupUi(this);
     m_plotXAxisThrehold= XAXIS_BASE_RANGE;
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    plot =CreateAndInitPlotGraph(QString("次数"),0,100,QString("网络延时"),-10,300,QRect(0,0,200,275));
    mainLayout->addWidget(plot);
}

plotdialog::~plotdialog()
{
    delete ui;
}

QCustomPlot* plotdialog::CreateAndInitPlotGraph(QString xLabel,int xRangeL,int xRangeR,QString yLabel,int yRangeL,int yRangeR,QRect rect)
{
    QCustomPlot *customPlot = new QCustomPlot(this);
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

void plotdialog::updateGraph(double point_x, double point_y)

       {
       if(point_x > m_plotXAxisThrehold)
        processPlotXAxisExpand(point_x);
        plot->graph(0)->addData(point_x,point_y);
        plot->replot();
       }

void plotdialog::processPlotXAxisExpand(double point_x)
{
      if(point_x != 0)
            {m_plotXAxisThrehold = point_x;
            plot->xAxis->setRange(0,1.25*m_plotXAxisThrehold);}
    plot->replot();
}
