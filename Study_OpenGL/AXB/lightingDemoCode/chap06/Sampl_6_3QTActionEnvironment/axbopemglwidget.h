#ifndef AXBOPEMGLWIDGET_H
#define AXBOPEMGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QTime>
#include <QTimer>
#include <QWheelEvent>
#include "camera.h"
#include <QOpenGLTexture>
#include "environmentsettingdialog.h"
class AXBOpemglWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit AXBOpemglWidget(QWidget *parent = nullptr);
    ~AXBOpemglWidget();

    void setEnvironmentType(EnvironmentSettingDialog::EnvironmentType type);

    EnvironmentSettingDialog::EnvironmentType type() const;
    void setType(const EnvironmentSettingDialog::EnvironmentType &type);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
    void on_timeout();
private:
    QTime m_time;
    QTimer m_timer;
    QOpenGLShaderProgram m_ShaderProgram;
    QOpenGLShaderProgram m_LightShaderProgram;
    Camera m_camera;
    QOpenGLTexture * m_diffuseTex;
    QOpenGLTexture * m_specularTex;

    QVector3D m_clearColor;
    QVector3D m_dirlight_ambient;
    QVector3D m_dirlight_diffuse;
    QVector3D m_dirlight_specular;
    EnvironmentSettingDialog::EnvironmentType m_type;

};


#endif // AXBOPEMGLWIDGET_H
