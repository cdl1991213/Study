#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//创建画出两个并排的三角形【一个VAO和一个VBO】
//创建画出两个并排的三角形【多个VAO和多个VBO】

//创建画出两个并排的三角形,使用不同着色器
