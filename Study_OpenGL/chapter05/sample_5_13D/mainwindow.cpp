#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);   //将widget覆盖整个mainwindow
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_clear_triggered()        //清空图形
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::None);
}


void MainWindow::on_action_3D_triggered()       //画3D
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::ThreeD);
}

void MainWindow::on_action_3D_Rotate_triggered()    //画旋转3D
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::ThreeD_Rotate);
}

void MainWindow::on_action_rect_triggered()     //画矩形
{
    //传入枚举量Shape{None, Rect, Circle, Triangle}
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect);
}

void MainWindow::on_action_rect_tecture_triggered()     //画纹理矩形
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect_Tecture);
}

void MainWindow::on_action_rect_tecture_dynamic_triggered()     //画动态纹理矩阵
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect_Tecture_ManualDynamic);
}

void MainWindow::on_action_triangle_triggered()     //画三角
{
    //传入枚举量Shape{None, Rect, Circle, Triangle}
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Triangle);
}

void MainWindow::on_action_setWireFrame_triggered()     //线框模式
{
    ui->openGLWidget->setWireMode(ui->action_setWireFrame->isChecked());
}


