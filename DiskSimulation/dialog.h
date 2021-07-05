#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    QLabel *l1,*l2,*l3,*l4,*l5,*l6,*l7,*l8,*l9,*l10,*l11,*l12,*l13;
    QPushButton *btn1,*btn2,*btn3,*btn4,*btn5;
    QLineEdit *li1,*li2,*li3,*li4,*li5,*li6,*li7;
//    QLabel *w1,*w2,*w3,*w4,*w5,*w6,*w7;
private slots:
    void case0out();
    void case1out();
    void case2out();
    void case3out();
};

#endif // DIALOG_H
