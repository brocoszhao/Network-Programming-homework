#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0,Qt::WindowFlags f=0);
    ~Dialog();

private:
   QLabel *InfoLabel;
   QListWidget *ContentListWidget;
   QLabel *PortLabel;
   QLineEdit *PortLineEdit;
   QPushButton *StartButton;
   QGridLayout *mainLayout;
};

#endif // DIALOG_H
