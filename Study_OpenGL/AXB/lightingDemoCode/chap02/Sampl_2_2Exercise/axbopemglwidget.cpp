#include "axbopemglwidget.h"

float vertices[] = {
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
 };


const unsigned int timeOutmSec=50;
unsigned int VAO,VBO,lightVAO;
QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D objectColor(1.0f, 0.5f, 0.31f);

AXBOpemglWidget::AXBOpemglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    m_timer.start(timeOutmSec);
    m_time.start();
    m_camera.Position=QVector3D(0.0,0.0,5.0);
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
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //绑定VBO和VAO对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    bool success;
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/shapes.vert");
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/shapes.frag");
    success=m_ShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_ShaderProgram.log();


    m_LightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/light.vert");
    m_LightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/light.frag");
    success=m_LightShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_LightShaderProgram.log();
    m_LightShaderProgram.bind();
    m_LightShaderProgram.setUniformValue("lightColor",lightColor);
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
    projection.perspective(m_camera.Zoom,(float)width()/height(),0.1,100); view=m_camera.GetViewMatrix(); glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_ShaderProgram.bind();
    m_ShaderProgram.setUniformValue("projection", projection);
    m_ShaderProgram.setUniformValue("view", view);
    model.rotate(time, 1.0f, 5.0f, 0.5f);
    m_ShaderProgram.setUniformValue("model", model);
    m_ShaderProgram.setUniformValue("objectColor",objectColor);
    m_ShaderProgram.setUniformValue("lightColor",lightColor);
    lightPos.setX(cos(time/50)*2.5);
    lightPos.setZ(sin(time/50)*2.5);
    m_ShaderProgram.setUniformValue("lightPos",lightPos);
    m_ShaderProgram.setUniformValue("viewPos",m_camera.Position);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,36);

    m_LightShaderProgram.bind();
    m_LightShaderProgram.setUniformValue("projection", projection);
    m_LightShaderProgram.setUniformValue("view", view);
    model.setToIdentity();
    model.translate(lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.2);
    m_LightShaderProgram.setUniformValue("model", model);
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void AXBOpemglWidget::on_timeout()
{
    update();
}
