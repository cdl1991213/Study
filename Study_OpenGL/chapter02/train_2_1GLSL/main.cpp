#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


//三角形水平上下颠倒
//gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f)  -->   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0f)

//三角形水平偏移xOffset

//out 将顶点位置设置为片段着色器的颜色
