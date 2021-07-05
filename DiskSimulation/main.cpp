#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;

    w.setWindowTitle("欢迎来到磁盘操作系统");

    w.show();

    return a.exec();
}
