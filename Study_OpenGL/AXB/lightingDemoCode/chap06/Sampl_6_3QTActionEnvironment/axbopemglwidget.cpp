#include "axbopemglwidget.h"

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
QVector3D cubePositions[] = {
    QVector3D( 0.0f, 0.0f, 0.0f),
    QVector3D( 2.0f, 5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D( 2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f, 3.0f, -7.5f),
    QVector3D( 1.3f, -2.0f, -2.5f),
    QVector3D( 1.5f, 2.0f, -2.5f),
    QVector3D( 1.5f, 0.2f, -1.5f),
    QVector3D(-1.3f, 1.0f, -1.5f)
};
QVector3D pointLightPositions[] = {
    QVector3D( 0.7f, 0.2f, 2.0f),
    QVector3D( 2.3f, -3.3f, -4.0f),
    QVector3D(-4.0f, 2.0f, -12.0f),
    QVector3D( 0.0f, 0.0f, -3.0f)
};

QVector3D pointLightColors[4];
QVector3D pointLightColorsDesert[] = {
    QVector3D(1.0f, 0.6f, 0.0f),
    QVector3D(1.0f, 0.0f, 0.0f),
    QVector3D(1.0f, 1.0, 0.0),
    QVector3D(0.2f, 0.2f, 1.0f)
};
QVector3D pointLightColorsFactory[] = {
    QVector3D(0.2f, 0.2f, 0.6f),
    QVector3D(0.3f, 0.3f, 0.7f),
    QVector3D(0.0f, 0.0f, 0.3f),
    QVector3D(0.4f, 0.4f, 0.4f)
};
QVector3D pointLightColorsHorror[] = {
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.3f, 0.1f, 0.1f)
};
QVector3D pointLightColorsBiochemicalLab[] = {
    QVector3D(1.0f, 0.6f, 0.0f),
    QVector3D(1.0f, 0.0f, 0.0f),
    QVector3D(1.0f, 1.0, 0.0),
    QVector3D(0.2f, 0.2f, 1.0f) }
;


const unsigned int timeOutmSec=50;
unsigned int VAO,VBO,lightVAO;
QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D objectColor(1.0f, 0.5f, 0.31f);
QVector3D viewInitPos(0.0,0.0,5.0);
const float PI=3.1415926;

AXBOpemglWidget::AXBOpemglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    m_timer.start(timeOutmSec);
    m_time.start();
    m_camera.Position=viewInitPos;
    setFocusPolicy(Qt::StrongFocus);
    setEnvironmentType(EnvironmentSettingDialog::DESERT);
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

void AXBOpemglWidget::setEnvironmentType(EnvironmentSettingDialog::EnvironmentType type)
{
    m_type=type;
    switch (type) {
    case EnvironmentSettingDialog::DESERT:
        m_clearColor=QVector3D(0.75f, 0.52f, 0.3f);
        m_dirlight_ambient=QVector3D(0.3f, 0.24f, 0.14f);
        m_dirlight_diffuse=QVector3D(0.7f, 0.42f, 0.26f);
        m_dirlight_specular=QVector3D(0.5f, 0.5f, 0.5f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsDesert[i];
        break;
    case EnvironmentSettingDialog::FACTTORY:
        m_clearColor=QVector3D(0.0f, 0.0f, 0.0f);
        m_dirlight_ambient=QVector3D(0.05f, 0.05f, 0.1f);
        m_dirlight_diffuse=QVector3D(0.2f, 0.2f, 0.7);
        m_dirlight_specular=QVector3D(0.7f, 0.7f, 0.7f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsFactory[i];
        break;
    case EnvironmentSettingDialog::HORROR:
        m_clearColor=QVector3D(0.0f, 0.0f, 0.0f);
        m_dirlight_ambient=QVector3D(0.0f, 0.0f, 0.0f);
        m_dirlight_diffuse=QVector3D(0.05f, 0.05f, 0.05);
        m_dirlight_specular=QVector3D(0.2f, 0.2f, 0.2f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsHorror[i];
        break;
    case EnvironmentSettingDialog::BIOCHEMICALLAB:
        m_clearColor=QVector3D(0.9f, 0.9f, 0.9f);
        m_dirlight_ambient=QVector3D(0.5f, 0.5f, 0.5f);
        m_dirlight_diffuse=QVector3D(1.0f, 1.0f, 1.0f);
        m_dirlight_specular=QVector3D(1.0f, 1.0f, 1.0f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsBiochemicalLab[i];
        break;
    default:
        break;
    }
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    bool success;
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/shapes.vert");
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/shapes.frag");
    success=m_ShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_ShaderProgram.log();

    m_diffuseTex=new QOpenGLTexture(QImage(":/images/images/container2.png").mirrored());
    m_specularTex=new QOpenGLTexture(QImage(":/images/images/container2_specular.png").mirrored());
    m_ShaderProgram.bind();
    m_ShaderProgram.setUniformValue("material.diffuse", 0);
    m_ShaderProgram.setUniformValue("material.specular", 1);


    m_LightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/light.vert");
    m_LightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/light.frag");
    success=m_LightShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_LightShaderProgram.log();

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
    //float time=m_time.elapsed()/50.0;
    projection.perspective(m_camera.Zoom,(float)width()/height(),0.1,100);
    view=m_camera.GetViewMatrix();
    glClearColor(m_clearColor.x(), m_clearColor.y(),m_clearColor.z(), 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_ShaderProgram.bind();
    m_ShaderProgram.setUniformValue("projection", projection);
    m_ShaderProgram.setUniformValue("view", view);
    m_ShaderProgram.setUniformValue("viewPos",m_camera.Position);

    //spotLight
    m_ShaderProgram.setUniformValue("spotLight.position", m_camera.Position);
    m_ShaderProgram.setUniformValue("spotLight.direction", m_camera.Front);
    m_ShaderProgram.setUniformValue("spotLight.cutOff", (float)cos(12.5f*PI/180) );
    m_ShaderProgram.setUniformValue("spotLight.outerCutOff", (float)cos(17.5f*PI/180));

    m_ShaderProgram.setUniformValue("spotLight.ambient", 0.4f, 0.4f, 0.4f);
    m_ShaderProgram.setUniformValue("spotLight.diffuse", 0.9f, 0.9f, 0.9f);
    m_ShaderProgram.setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);

    m_ShaderProgram.setUniformValue("spotLight.constant", 1.0f);
    m_ShaderProgram.setUniformValue("spotLight.linear", 0.09f);
    m_ShaderProgram.setUniformValue("spotLight.quadratic", 0.032f);

    // directional light
    m_ShaderProgram.setUniformValue("dirLight.direction", -0.2f, -1.0f, -0.3f);
    m_ShaderProgram.setUniformValue("dirLight.ambient", m_dirlight_ambient);
    m_ShaderProgram.setUniformValue("dirLight.diffuse", m_dirlight_diffuse);
    m_ShaderProgram.setUniformValue("dirLight.specular", m_dirlight_specular);

    // point lights
    for(int i=0;i<4;i++){
        QString iStr="pointLights["+QString::number(i)+"].position";
        m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), pointLightPositions[i].x(), pointLightPositions[i].y(), pointLightPositions[i].z());
        iStr="pointLights["+QString::number(i)+"].ambient";
        m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), pointLightColors[i].x() * 0.1, pointLightColors[i].y() * 0.1, pointLightColors[i].z() * 0.1);
        iStr="pointLights["+QString::number(i)+"].diffuse";
        m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), pointLightColors[i].x(), pointLightColors[i].y(), pointLightColors[i].z());
        iStr="pointLights["+QString::number(i)+"].specular";
        m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), pointLightColors[i].x(), pointLightColors[i].y(), pointLightColors[i].z());
        iStr="pointLights["+QString::number(i)+"].constant"; m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), 1.0f);
        iStr="pointLights["+QString::number(i)+"].linear";
        m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), 0.09f);
        iStr="pointLights["+QString::number(i)+"].quadratic";
        m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(), 0.032f);
    }

    // material properties
    m_ShaderProgram.setUniformValue("material.shininess", 32.0f);

    m_diffuseTex->bind(0);
    m_specularTex->bind(1);
    glBindVertexArray(VAO);
    // positions all containers

    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        m_ShaderProgram.setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    m_LightShaderProgram.bind();
    m_LightShaderProgram.setUniformValue("projection", projection);
    m_LightShaderProgram.setUniformValue("view", view);


    model.rotate(1.0, 1.0f, 1.0f, 0.5f);
    model.scale(0.2);

    glBindVertexArray(lightVAO);
    for(int i=0;i<4;i++){
        model.setToIdentity();
        model.translate(pointLightPositions[i]);
        model.scale(0.2);
        m_LightShaderProgram.setUniformValue("model", model);
        m_LightShaderProgram.setUniformValue("lightColor",pointLightColors[i]);
        glDrawArrays(GL_TRIANGLES,0,36);
    }
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

EnvironmentSettingDialog::EnvironmentType AXBOpemglWidget::type() const
{
    return m_type;
}

void AXBOpemglWidget::setType(const EnvironmentSettingDialog::EnvironmentType &type)
{
    m_type = type;
}

