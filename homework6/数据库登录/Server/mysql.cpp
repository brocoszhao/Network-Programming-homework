#include "mysql.h"
#include<QtDebug>

MySql::MySql()
{

}

void MySql::initsql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("!@#123");
    db.setDatabaseName("qtLogin.db");
    if(db.open())
        {
            qDebug()<<"Database connected successfully!";
            createtable();
            return;
        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }
}

void MySql::createtable()
{
    query=new QSqlQuery;

    bool success=query->exec("create table user(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,passward VARCHAR(30))");
    if(success)
        qDebug()<<QObject::tr("数据库表创建成功！\n");
    else
        qDebug()<<QObject::tr("数据库表创建失败！\n");
    /*创建root用户*/
    query->exec("insert into user values('root2', 'root2')");
}


bool MySql::loguser(QString name, QString passward)
{
    QString str=QString("select * from user where name='%1' and passward='%2'").arg(name).arg(passward);
    qDebug()<<str;
    query=new QSqlQuery;
    query->exec(str);
    query->last();
    int record=query->at()+1;
    qDebug()<<record;
    if(record==-1)
        return false;
    return true;
}


bool MySql::signup(QString name,QString passward)
{
    QString str=QString("select * from user where name='%1'").arg(name);
    qDebug()<<str;
    query=new QSqlQuery;
    query->exec(str);
    query->last();
    int record=query->at()+1;
    qDebug()<<record;
    if(record==1)
        return false;
    QString str2=QString("insert into user values('%1','%2')").arg(name).arg(passward);
    qDebug()<<str2;
    bool ret=query->exec(str2);
    qDebug()<<ret;
    return ret;
}
