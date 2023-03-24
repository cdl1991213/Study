#include "cdlopenglwidget.h"

unsigned int VAO, VBO, lightVAO;
QVector3D lightPos(1.2f, 1.0f, 2.0f);       //光源位置
QVector3D lightColor(1.0f, 1.0f, 1.0f);     //光源
QVector3D viewInitPos(0.0, 0.0, 5.0);
const float PI=3.1415926;

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

const unsigned int timeOutSec = 50;
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    Timer.start(timeOutSec);    //计时器
    Time.start();               //时刻
    //(发出信号的对象A， 对象A的信号， 接收信号的对象B， 需要调用的对象B的函数)
    connect(&Timer, SIGNAL(timeout()), this, SLOT(on_timeout()));

    setFocusPolicy(Qt::StrongFocus);    //关注键盘输入
    setMouseTracking(true);             //关注鼠标移动

    clearColor=QVector3D(0.9f, 0.9f, 0.9f);
    dirlight_ambient=QVector3D(0.5f, 0.5f, 0.5f);
    dirlight_diffuse=QVector3D(1.0f, 1.0f, 1.0f);
    dirlight_specular=QVector3D(1.0f, 1.0f, 1.0f);

    Camera.Position = QVector3D(0, 0, 5.0);  //初始化camera位置为z=3
}

cdlOpenGLWidget::~cdlOpenGLWidget()
{
    if(isValid()){return;}  //程序对象初始化发生错误（如initializeGL(),resizeGL(),paintGL()）

    makeCurrent();  //调出当前状态
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    doneCurrent();  //退出当前状态

}

//-------------------------------------------------------------toolbar-------------------------------------------------------



//--------------------------------------------------------------主程序--------------------------------------------------------



void cdlOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //--------------------------------------------------------------------------------------------------
    //############################################着色器 ShaderProgram_ThreeD_multiLight#################
    //--------------------------------------------------------------------------------------------------
    bool success_ThreeD_multiLight;   //是否成功
    ShaderProgram_ThreeD_multiLight.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    ShaderProgram_ThreeD_multiLight.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    success_ThreeD_multiLight = ShaderProgram_ThreeD_multiLight.link();
    if(!success_ThreeD_multiLight){
        qDebug()<<"ERR:"<<ShaderProgram_ThreeD_multiLight.log();
    }
    //纹理图案
    ShaderProgram_ThreeD_multiLight.bind();

    //--------------------------------------------------------------------------------------------------
    //############################################着色器ShaderProgram_light##############################
    //--------------------------------------------------------------------------------------------------
    bool success_light;   //是否成功
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_light.vert");
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_light.frag");
    success_light = ShaderProgram_light.link();
    if(!success_light){
        qDebug()<<"ERR:"<<ShaderProgram_light.log();
    }

    //--------------------------------------------------------------------------------------------------
    //############################################模型库#################################################
    //--------------------------------------------------------------------------------------------------
    myModel = new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                        , "D:/Study/file/demo/OpenGL/chapter07/backpack/backpack.obj");
    //--------------------------------------------------------------------------------------------------
    //############################################纹理库#################################################
    //--------------------------------------------------------------------------------------------------
    //纹理效果————背景为透明image.png不自动填充背景色
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //纹理库
//    diffuseTexture = new QOpenGLTexture(QImage(":/images/images/container2.png").mirrored());
//    specularTexture = new QOpenGLTexture(QImage(":/images/images/container2_specular.png").mirrored());

    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------------------
}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void cdlOpenGLWidget::paintGL()
{
    glClearColor(clearColor.x(), clearColor.y(), clearColor.z(), 1.0f);       //初始化Widget BackgroundColor
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;      //初始化变换矩阵
    unsigned int time = QTime::currentTime().msec();    //获取当前时间
    float time1 = Time.elapsed()/50.0;

    QMatrix4x4 model;   //3D变换矩阵    物体对象
    QMatrix4x4 view;    //3D观察矩阵    摄像机
    QMatrix4x4 projection;      //3D投影矩阵    画布投影

    //-------------------------------obj 物体-------------------------
    //-----------着色器------------
    ShaderProgram_ThreeD_multiLight.bind();
    //------------3D矩阵-----------
    /*
     * view         摄像机
     * model        物体对象
     * projection   画布投影
    */
    //view
    view = Camera.GetViewMatrix();
//    view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
    ShaderProgram_ThreeD_multiLight.setUniformValue("view", view);
    ShaderProgram_ThreeD_multiLight.setUniformValue("viewPos", Camera.Position);
    //projection
    //(摄像机位置，窗口大小，近点位置，远点位置)
    projection.perspective(Camera.Zoom, (float)width()/(float)height(), 0.1, 100);
    ShaderProgram_ThreeD_multiLight.setUniformValue("projection", projection);
    //model
    //(旋转角度，x轴旋转比例，y轴旋转比例，z轴旋转比例)
    model.rotate(time1, 1.0f, 1.0f, 0.5f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("model", model);
    //material
    ShaderProgram_ThreeD_multiLight.setUniformValue("material.shininess", 32.0f);

    //SpotLight
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.position", Camera.Position);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.direction", Camera.Front);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.cutOff", (float)cos(12.5f*PI/180) );
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.outerCutOff", (float)cos(17.5f*PI/180) );
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.ambient", 0.4f, 0.4f, 0.4f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.diffuse", 0.9f, 0.9f, 0.9f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.specular", 1.0f, 1.0f, 1.0f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.constant", 1.0f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.linear", 0.09f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("spotlight.quadratic", 0.032f);
    //DirLight
    ShaderProgram_ThreeD_multiLight.setUniformValue("dirlight.direction", -0.2f, -1.0f, -0.3f);
    ShaderProgram_ThreeD_multiLight.setUniformValue("dirlight.ambient", dirlight_ambient);
    ShaderProgram_ThreeD_multiLight.setUniformValue("dirlight.diffuse", dirlight_diffuse);
    ShaderProgram_ThreeD_multiLight.setUniformValue("dirlight.specular", dirlight_specular);
    //PointLights
    for(int i=0;i<4;i++){
        QString iStr="pointlights["+QString::number(i)+"].position";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), pointLightPositions[i].x(), pointLightPositions[i].y(), pointLightPositions[i].z());
        iStr="pointlights["+QString::number(i)+"].ambient";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), pointLightColors[i].x() * 0.1, pointLightColors[i].y() * 0.1, pointLightColors[i].z() * 0.1);
        iStr="pointlights["+QString::number(i)+"].diffuse";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), pointLightColors[i].x(), pointLightColors[i].y(), pointLightColors[i].z());
        iStr="pointlights["+QString::number(i)+"].specular";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), pointLightColors[i].x(), pointLightColors[i].y(), pointLightColors[i].z());
        iStr="pointlights["+QString::number(i)+"].constant";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), 1.0f);
        iStr="pointlights["+QString::number(i)+"].linear";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), 0.09f);
        iStr="pointlights["+QString::number(i)+"].quadratic";
        ShaderProgram_ThreeD_multiLight.setUniformValue(iStr.toStdString().c_str(), 0.032f);
    }

    myModel->Draw(ShaderProgram_ThreeD_multiLight);

}
//---------------------------------------------------------------------------------------------------------------------------
void cdlOpenGLWidget::on_timeout()
{
    update();   //重新执行paintGL()
}
//----------------------------------------------------camera class-----------------------------------------------------------
//鼠标滚轮
void cdlOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    Camera.ProcessMouseScroll(event -> angleDelta().y()/120);
}

//键盘
void cdlOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    float deltaTime = timeOutSec / 1000.0;
    switch (event -> key()) {
    //wasd移动camera
    case Qt::Key_W:
        Camera.ProcessKeyboard(FORWARD, deltaTime);
        break;
    case Qt::Key_S:
        Camera.ProcessKeyboard(BACKWARD, deltaTime);
        break;
    case Qt::Key_D:
        Camera.ProcessKeyboard(RIGHT, deltaTime);
        break;
    case Qt::Key_A:
        Camera.ProcessKeyboard(LEFT, deltaTime);
        break;
    case Qt::Key_E:
        Camera.ProcessKeyboard(DOWN, deltaTime);
        break;
    case Qt::Key_Q:
        Camera.ProcessKeyboard(UP, deltaTime);
        break;
    case Qt::Key_Space:
        Camera.Position = viewInitPos;  //camera恢复原位
        break;
    default:
        break;
    }

    update();
}

//鼠标移动
QPoint deltaPos;
void cdlOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标右键为启动条件
    if(event -> buttons() & Qt::RightButton){
        static QPoint lastPos(width()/2, height()/2);
        auto currentPos = event -> pos();
        deltaPos = currentPos - lastPos;
        lastPos = currentPos;

        Camera.ProcessMouseMovement(deltaPos.x(), -deltaPos.y());
    }

    update();

}

