#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//画出一个三角形，并着色【一个VAO和一个VBO】

//画出一个（由两个三角形拼成）矩形，并着色【一个VAO和多个VBO】
//画出一个（由两个三角形拼成）矩形，只着色矩形边

//借助EBO，画出一个（由两个三角形拼成）矩形【一个VAO和一个VBO＋EBO】
