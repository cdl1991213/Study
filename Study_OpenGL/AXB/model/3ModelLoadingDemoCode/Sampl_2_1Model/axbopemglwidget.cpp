#include "axbopemglwidget.h"

const unsigned int timeOutmSec=50;
unsigned int VAO,VBO,lightVAO;
QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D objectColor(1.0f, 0.5f, 0.31f);
QVector3D viewInitPos(0.0,0.0,5.0);
AXBOpemglWidget::AXBOpemglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    m_timer.start(timeOutmSec);
    m_time.start();
    m_camera.Position=viewInitPos;
    setFocusPolicy(Qt::StrongFocus);
    //setMouseTracking(true);
}

AXBOpemglWidget::~AXBOpemglWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteVertexArrays(1,&lightVAO);
    doneCurrent();
}

void AXBOpemglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //创建VBO和VAO对象，并赋予ID
    bool success;
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/shapes.vert");
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/shapes.frag");
    success=m_ShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_ShaderProgram.log();

  //  m_ShaderProgram.bind();

    m_model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                ,"D:/Qt/3ModelLoadingDemoCode/backpack/backpack.obj");
}

void AXBOpemglWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void AXBOpemglWidget::paintGL()
{
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    float time=m_time.elapsed()/50.0;
    projection.perspective(m_camera.Zoom,(float)width()/height(),0.1,100);
    view=m_camera.GetViewMatrix();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_ShaderProgram.bind();
    m_ShaderProgram.setUniformValue("projection", projection);
    m_ShaderProgram.setUniformValue("view", view);
    model.rotate(time, 1.0f, 1.0f, 0.5f);

    m_ShaderProgram.setUniformValue("viewPos",m_camera.Position);

    // light properties, note that all light colors are set at full intensity
    m_ShaderProgram.setUniformValue("light.ambient", 0.4f, 0.4f, 0.4f);
    m_ShaderProgram.setUniformValue("light.diffuse", 0.9f, 0.9f, 0.9f);
    m_ShaderProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    // material properties
    m_ShaderProgram.setUniformValue("material.shininess", 32.0f);
    m_ShaderProgram.setUniformValue("light.direction", -0.2f, -1.0f, -0.3f);
    m_ShaderProgram.setUniformValue("model", model);
    m_model->Draw(m_ShaderProgram);
}

void AXBOpemglWidget::wheelEvent(QWheelEvent *event)
{
    m_camera.ProcessMouseScroll(event->angleDelta().y()/120);
}

void AXBOpemglWidget::keyPressEvent(QKeyEvent *event)
{
    float deltaTime=timeOutmSec/1000.0;

    switch (event->key()) {
    case Qt::Key_W: m_camera.ProcessKeyboard(FORWARD,deltaTime);break;
    case Qt::Key_S: m_camera.ProcessKeyboard(BACKWARD,deltaTime);break;
    case Qt::Key_D: m_camera.ProcessKeyboard(RIGHT,deltaTime);break;
    case Qt::Key_A: m_camera.ProcessKeyboard(LEFT,deltaTime);break;
    case Qt::Key_Q: m_camera.ProcessKeyboard(DOWN,deltaTime);break;
    case Qt::Key_E: m_camera.ProcessKeyboard(UP,deltaTime);break;
    case Qt::Key_Space: m_camera.Position=viewInitPos;break;

    default:break;
    }
}

void AXBOpemglWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton){
        static QPoint lastPos(width()/2,height()/2);
        auto currentPos=event->pos();
        QPoint deltaPos=currentPos-lastPos;
        lastPos=currentPos;

        m_camera.ProcessMouseMovement(deltaPos.x(),-deltaPos.y());
    }
}

void AXBOpemglWidget::on_timeout()
{
    update();
}
