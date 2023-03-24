#ifndef CDLOPENGLWIDGET_H
#define CDLOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>         //着色器
#include <QOpenGLTexture>               //纹理
#include <QTime>                        //时间
#include <QTimer>                       //计时器
#include <QKeyEvent>                    //键盘按键

#include "math.h"                       //数学公式
#include "camera.h"                     //3D相机
#include "setenvironmentdialog.h"

#include "meshforonce.h"                //绘制最小单元mesh
#include "model.h"                      //模型加载
class cdlOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit cdlOpenGLWidget(QWidget *parent = nullptr);
    ~cdlOpenGLWidget();

    enum Shape{None, Triangle, Rect_1, Rect_2, Rect_3, ThreeD_1, ThreeD_2, Model_1};
    void drawShape(Shape shape);
    void setWireMode(bool mode);    //线框模式
    void loadModel(string path);    //加载模型


    void setEnvironment(setEnvironmentDialog::EnvironmentType environment);     //修改环境参数

    setEnvironmentDialog::EnvironmentType getMyEnvironment() const;                     //get
    void setMyEnvironment(const setEnvironmentDialog::EnvironmentType &value);          //set

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void wheelEvent(QWheelEvent * event);       //鼠标滚轮
    void mouseMoveEvent(QMouseEvent * event);   //鼠标移动
    void keyPressEvent(QKeyEvent * event);      //键盘按键

private:
    QTimer Timer;
    QTime Time;
    Camera Camera;
    QOpenGLShaderProgram ShaderProgram_withoutTexture, ShaderProgram_withTexture, ShaderProgram_ThreeD, ShaderProgram_ThreeD_multiLight, ShaderProgram_light;
    QOpenGLTexture * Wall, * Container, * Container_specular, * PandaLisa, * diffuseTexture, * specularTexture, * emissionTexture;
    Shape myShape; 

    Mesh_once * myMesh;
    Mesh_once* processMess();

    Model * myModel = NULL;
    QVector3D cameraPosInit(float maxY,float minY);     //根据模型Y坐标极值，设置不同模型的相机初始位置

    QVector3D clearColor;
    QVector3D dirlight_ambient;
    QVector3D dirlight_diffuse;
    QVector3D dirlight_specular;

    setEnvironmentDialog::EnvironmentType myEnvironment;


public slots:   //信号槽机制(slots槽，接受系统signals信号)
    void on_timeout();

signals:

};

#endif // CDLOPENGLWIDGET_H

