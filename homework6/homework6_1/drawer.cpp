#include "drawer.h"
#include<QGroupBox>
#include<QVBoxLayout>

Drawer::Drawer(QWidget *parent,Qt::WindowFlags f)
    :QToolBox(parent,f)
{
   setWindowTitle(tr("我的好友"));
   setWindowIcon(QPixmap(":/images/qq.png"));

   toolBtn1 =new QToolButton;
   toolBtn1->setText(tr("江忠涛"));
   toolBtn1->setIcon(QPixmap(":/images/spqy.png"));
   toolBtn1->setIconSize(QPixmap(":/images/spqy.png").size());
   toolBtn1->setAutoRaise(true);
   toolBtn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn1,SIGNAL(clicked()),this,SLOT(showChatWidget1()));

   toolBtn2 =new QToolButton;
   toolBtn2->setText(tr("魏书洋"));
   toolBtn2->setIcon(QPixmap(":/images/ymrl.png"));
   toolBtn2->setIconSize(QPixmap(":/images/ymrl.png").size());
   toolBtn2->setAutoRaise(true);
   toolBtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn2,SIGNAL(clicked()),this,SLOT(showChatWidget2()));

   toolBtn3 =new QToolButton;
   toolBtn3->setText(tr("王俊林"));
   toolBtn3->setIcon(QPixmap(":/images/qq.png"));
   toolBtn3->setIconSize(QPixmap(":/images/qq.png").size());
   toolBtn3->setAutoRaise(true);
   toolBtn3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn3,SIGNAL(clicked()),this,SLOT(showChatWidget3()));

   toolBtn4 =new QToolButton;
   toolBtn4->setText(tr("Cherry"));
   toolBtn4->setIcon(QPixmap(":/images/Cherry.png"));
   toolBtn4->setIconSize(QPixmap(":/images/Cherry.png").size());
   toolBtn4->setAutoRaise(true);
   toolBtn4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn4,SIGNAL(clicked()),this,SLOT(showChatWidget4()));

   toolBtn5 =new QToolButton;
   toolBtn5->setText(tr("haha"));
   toolBtn5->setIcon(QPixmap(":/images/dr.png"));
   toolBtn5->setIconSize(QPixmap(":/images/dr.png").size());
   toolBtn5->setAutoRaise(true);
   toolBtn5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn5,SIGNAL(clicked()),this,SLOT(showChatWidget5()));

   toolBtn6 =new QToolButton;
   toolBtn6->setText(tr("宋智孝"));
   toolBtn6->setIcon(QPixmap(":/images/jj.png"));
   toolBtn6->setIconSize(QPixmap(":/images/jj.png").size());
   toolBtn6->setAutoRaise(true);
   toolBtn6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  // connect(toolBtn6,SIGNAL(clicked()),this,SLOT(showChatWidget6()));

   toolBtn7 =new QToolButton;
   toolBtn7->setText(tr("刘在石"));
   toolBtn7->setIcon(QPixmap(":/images/lswh.png"));
   toolBtn7->setIconSize(QPixmap(":/images/lswh.png").size());
   toolBtn7->setAutoRaise(true);
   toolBtn7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn7,SIGNAL(clicked()),this,SLOT(showChatWidget7()));

   toolBtn8 =new QToolButton;
   toolBtn8->setText(tr("青墨暖暖"));
   toolBtn8->setIcon(QPixmap(":/images/qmnn.png"));
   toolBtn8->setIconSize(QPixmap(":/images/qmnn.png").size());
   toolBtn8->setAutoRaise(true);
   toolBtn8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn8,SIGNAL(clicked()),this,SLOT(showChatWidget8()));

   toolBtn9 =new QToolButton;
   toolBtn9->setText(tr("王者"));
   toolBtn9->setIcon(QPixmap(":/images/wy.png"));
   toolBtn9->setIconSize(QPixmap(":/images/wy.png").size());
   toolBtn9->setAutoRaise(true);
   toolBtn9->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   //connect(toolBtn9,SIGNAL(clicked()),this,SLOT(showChatWidget9()));

}
