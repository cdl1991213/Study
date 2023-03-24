#ifndef CDLOPENGLWIDGET_H
#define CDLOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram> //着色器
#include <QOpenGLTexture>   //纹理
#include <QTime>    //时间
#include <QTimer>   //计时器
#include <QKeyEvent>
#include <math.h>

class cdlOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit cdlOpenGLWidget(QWidget *parent = nullptr);
    ~cdlOpenGLWidget();

    //画图形
    enum Shape{None, Rect, Rect_Tecture, Rect_Tecture_ManualDynamic, Circle, Triangle};
    void drawShape(Shape shape);
    //线框模式
    void setWireMode(bool mode);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void keyPressEvent(QKeyEvent * event);

private:
    QOpenGLShaderProgram ShaderProgram_fundamental, ShaderProgram_texture, ShaderProgram_texture_manual;
    QOpenGLTexture * PandaLisa, * rabbit;
    Shape myShape;
    QTimer timer;

public slots:   //信号槽机制(slots槽，接受系统signals信号)
    void on_timeout();

signals:

};

#endif // CDLOPENGLWIDGET_H
