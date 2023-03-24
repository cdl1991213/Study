#ifndef CDLOPENGLWIDGET_H
#define CDLOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram> //着色器
#include <QOpenGLTexture>   //纹理
#include <QTime>    //时间
#include <QTimer>   //计时器
#include <QKeyEvent>    //键盘按键
#include <math.h>       //数学算法
#include <camera.h> //3D相机

class cdlOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit cdlOpenGLWidget(QWidget *parent = nullptr);
    ~cdlOpenGLWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void wheelEvent(QWheelEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
private:
    QTime time;
    QTimer timer;
    Camera camera;
    QOpenGLShaderProgram ShaderProgram, ShaderProgram_light;
    QOpenGLTexture * diffuseTexture, * specularTexture, * emissionTexture;

public slots:   //信号槽机制(slots槽，接受系统signals信号)
    void on_timeout();
signals:

};

#endif // CDLOPENGLWIDGET_H
