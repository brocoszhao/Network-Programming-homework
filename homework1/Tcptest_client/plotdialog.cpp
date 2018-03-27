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
     ui->widget->show();

    //QHBoxLayout *mainLayout=new QHBoxLayout(this);
    //plot =CreateAndInitPlotGraph();
    //mainLayout->addWidget(plot);
}

plotdialog::~plotdialog()
{
    delete ui;
}
/*
QCustomPlot* plotdialog::CreateAndInitPlotGraph()
{
    QCustomPlot *customPlot = new QCustomPlot(this);
    customPlot->legend->setVisible(true);
    QFont lengendFont = font();
    customPlot->xAxis->setLabel("次数");
    customPlot->yAxis->setLabel("网络延时");
    lengendFont.setPointSize(9);
    customPlot->xAxis->setRange(0,100);
    customPlot->yAxis->setRange(-10,80);
    customPlot->legend->setFont(lengendFont);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
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
}*/
