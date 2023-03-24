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

void MainWindow::on_action_clear_triggered()    //清空图形
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::None);

}

void MainWindow::on_action_setWireFrame_triggered() //线框模式
{
    ui->openGLWidget->setWireMode(ui->action_setWireFrame->isChecked());
}

void MainWindow::on_action_triangle_triggered()     //画三角
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Triangle);
}

void MainWindow::on_action_rectangle_triggered()    //画矩形1
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect_1);
}

void MainWindow::on_action_rectangle2_triggered()   //画矩形2
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect_2);
}


void MainWindow::on_action_3D_1_triggered()     //3D视角图1
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::ThreeD_1);
}


void MainWindow::on_action_3D_2_triggered()     //3D视角图1
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::ThreeD_2);
}

void MainWindow::on_action_Model_1_triggered()      //模型1
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Model_1);
}


void MainWindow::on_action_setEnvironment_triggered()       //调出environmentDialog框,环境选择
{
    setEnvironmentDialog * dlg=new setEnvironmentDialog(this);

    dlg->setDialogLable(ui->openGLWidget->getMyEnvironment());  //选择框首选显示的当前正在使用的环境value值（cdlopenglwidget->dlg）
    if(dlg->exec()==QDialog::Accepted){
        ui->openGLWidget->setEnvironment(dlg->getMyEnvironment());//将在dlg中选择的环境值传给cdlopenglwidget（dlg->cdlopenglwidget）
    }

    delete dlg;
}



#include <QFileDialog>      //对话框
void MainWindow::on_action_loadModel_triggered()        //加载模型
{
    QString str=QFileDialog::getOpenFileName(this,"选择模型文件","",
                   "OBJ (*.obj);;FBX(*.fbx);;ALL FILES( *.* ) ");       //模型文件路径
    ui->openGLWidget->loadModel(str.toStdString());                     //将模型文件路径传入loadModel
}
