#ifndef CDLOPENGLWIDGET_H
#define CDLOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
//着色器
#include <QOpenGLShaderProgram>
//计时器
#include <QTimer>

class cdlOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    //cdlopenglwidget的构造函数和析构函数
    explicit cdlOpenGLWidget(QWidget *parent = nullptr);
    ~cdlOpenGLWidget();

    //UI交互动作
    enum Shape{None, Rect, Circle, Triangle};
    void drawShape(Shape shape);
    void setWireMode(bool mode);

// 需要重载的三个函数
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    Shape myShape;
    QOpenGLShaderProgram myShaderProgram;
    QTimer myTimer;

public slots:
    void on_timeout();

signals:

};

#endif // CDLOPENGLWIDGET_H
