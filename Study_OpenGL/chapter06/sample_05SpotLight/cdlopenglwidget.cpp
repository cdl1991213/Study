#include "cdlopenglwidget.h"

unsigned int VAO, VBO, lightVAO;
QVector3D lightPos(1.2f, 1.0f, 2.0f);       //光源位置
QVector3D lightColor(1.0f, 1.0f, 1.0f);     //光源

QVector3D viewInitPos(0.0, 0.0, 5.0);
const float PI=3.1415926;

float vertices_rectriangle_ebo_3D[] = {
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

QVector<QVector3D> cubePosition = {
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

const unsigned int timeOutSec = 50;
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    timer.start(timeOutSec);    //计时器
    time.start();               //时刻

    setFocusPolicy(Qt::StrongFocus);    //关注键盘输入
    setMouseTracking(true);             //关注鼠标移动

    camera.Position = QVector3D(0, 0, 5.0);  //camera放在z=3
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
    //############################################着色器ShaderProgram####################################
    //--------------------------------------------------------------------------------------------------
    bool success;   //是否成功
    ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    success = ShaderProgram.link();
    if(!success){
        qDebug()<<"ERR:"<<ShaderProgram.log();
    }
    //纹理图案
    ShaderProgram.bind();
    ShaderProgram.setUniformValue("material.diffuse", 0);      //通道0
    ShaderProgram.setUniformValue("material.specular", 1);      //通道1

    //--------------------------------------------------------------------------------------------------
    //############################################着色器ShaderProgram_light##############################
    //--------------------------------------------------------------------------------------------------
    bool success_light;   //是否成功
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_light.vert");
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_light.frag");
    success_light = ShaderProgram_light.link();
    if(!success){
        qDebug()<<"ERR:"<<ShaderProgram_light.log();
    }


    //--------------------------------------------------------------------------------------------------
    //############################################纹理库#################################################
    //--------------------------------------------------------------------------------------------------
    //纹理效果————背景为透明image.png不自动填充背景色
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //纹理库
    diffuseTexture = new QOpenGLTexture(QImage(":/images/images/container2.png").mirrored());
    specularTexture = new QOpenGLTexture(QImage(":/images/images/container2_specular.png").mirrored());
    diffuseTexture -> bind(0);
    specularTexture -> bind(1);

    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //-------------------------------------VAO-----------------------------------
    glBindVertexArray(VAO);
    //########绑定VBO#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_ebo_3D), vertices_rectriangle_ebo_3D, GL_STATIC_DRAW);
    //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //normals attribute_location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texcoords attribute_location = 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //-------------------------------------lightVAO-----------------------------------
    glBindVertexArray(lightVAO);
    //########绑定VBO#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_ebo_3D), vertices_rectriangle_ebo_3D, GL_STATIC_DRAW);
    //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //-------------------------------------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //--------------------------------------------------------------------------------------------------
}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void cdlOpenGLWidget::paintGL()
{
    //Widget
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 model;   //3D变换矩阵    物体对象
    QMatrix4x4 view;    //3D观察矩阵    摄像机
    QMatrix4x4 projection;      //3D投影矩阵    画布投影
//    unsigned int time = QTime::currentTime().msec();
    float time1 = time.elapsed()/50.0;

    //-------------------------------obj1 物体-------------------------
    //----------OpenGL对象---------
    glBindVertexArray(VAO);
    //-----------着色器------------
    ShaderProgram.bind();
    //------------纹理变换----------
    diffuseTexture -> bind(0);
    specularTexture -> bind(1);
    //------------3D矩阵-----------
    //view
    view = camera.GetViewMatrix();
//    view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
    ShaderProgram.setUniformValue("view", view);
    //projection
    projection.perspective(camera.Zoom, (float)width()/(float)height(), 0.1, 100);
    ShaderProgram.setUniformValue("projection", projection);
    //model
    model.rotate(time1, 1.0f, 1.0f, 0.5f);   //自转，绕y轴旋转
    ShaderProgram.setUniformValue("model", model);
    //物体材质
    ShaderProgram.setUniformValue("material.shininess", 32.0f);
    //光线颜色
//    lightColor.setX(sin(time1 / 100 * 2.0f));       //改变光线颜色
//    lightColor.setY(sin(time1 / 100 * 0.7f));
//    lightColor.setZ(sin(time1 / 100 * 1.3f));
//    QVector3D diffuseColor = lightColor * QVector3D(0.5, 0.5, 0.5);
//    QVector3D ambientColor = diffuseColor * QVector3D(0.2, 0.2, 0.2);
//    ShaderProgram.setUniformValue("light.ambient", ambientColor);
//    ShaderProgram.setUniformValue("light.diffuse", diffuseColor);
//    ShaderProgram.setUniformValue("light.specular", QVector3D(1.0, 1.0, 1.0));
    ShaderProgram.setUniformValue("light.position", camera.Position);
    ShaderProgram.setUniformValue("light.direction", camera.Front);
    ShaderProgram.setUniformValue("light.cutOff", (float)cos(12.5f*PI/180) );
    ShaderProgram.setUniformValue("light.outerCutOff", (float)cos(17.5f*PI/180) );
    ShaderProgram.setUniformValue("light.ambient", 0.4f, 0.4f, 0.4f);
    ShaderProgram.setUniformValue("light.diffuse", 0.9f, 0.9f, 0.9f);
    ShaderProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    ShaderProgram.setUniformValue("light.constant", 1.0f);
    ShaderProgram.setUniformValue("light.linear", 0.09f);
    ShaderProgram.setUniformValue("light.quadratic", 0.032f);
    //光源位置
//    lightPos.setX(cos(time1/100)*2.5);      //光源公转(物体受光照变化时需要用到光源的位置信息，因此在此传入)
//    lightPos.setZ(sin(time1/100)*2.5);
    ShaderProgram.setUniformValue("viewPos", camera.Position);

    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(cubePosition[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        model.rotate(time1, 1.0f, 1.0f, 0.5f);   //自转，绕y轴旋转
        ShaderProgram.setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER
    }

    //-------------------------------obj2 光源-------------------------
    //----------OpenGL对象---------
    glBindVertexArray(lightVAO);
    //-----------着色器------------
    ShaderProgram_light.bind();
    //------------3D矩阵-----------
    //view
//    view = camera.GetViewMatrix();
//    view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
    ShaderProgram_light.setUniformValue("view", view);
    //projection
//    projection.perspective(camera.Zoom, (float)width()/(float)height(), 0.1, 100);
    ShaderProgram_light.setUniformValue("projection", projection);
    //model
    model.setToIdentity();
    model.translate(lightPos);      //移动位置
    //rotate(旋转角度, x轴, y轴, z轴)
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);   //自传，绕y轴旋转
    model.scale(0.2);
    ShaderProgram_light.setUniformValue("model", model);
    //光源颜色
    ShaderProgram_light.setUniformValue("lightColor", lightColor);

    glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER




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
    camera.ProcessMouseScroll(event -> angleDelta().y()/120);
}

//键盘
void cdlOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    float deltaTime = timeOutSec / 1000.0;
    switch (event -> key()) {
    //wasd移动camera
    case Qt::Key_W:
        camera.ProcessKeyboard(FORWARD, deltaTime);
        break;
    case Qt::Key_S:
        camera.ProcessKeyboard(BACKWARD, deltaTime);
        break;
    case Qt::Key_A:
        camera.ProcessKeyboard(RIGHT, deltaTime);
        break;
    case Qt::Key_D:
        camera.ProcessKeyboard(LEFT, deltaTime);
        break;
    case Qt::Key_Q:
        camera.ProcessKeyboard(DOWN, deltaTime);
        break;
    case Qt::Key_E:
        camera.ProcessKeyboard(UP, deltaTime);
        break;
    case Qt::Key_Space:
        camera.Position = viewInitPos;  //camera恢复原位
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

        camera.ProcessMouseMovement(deltaPos.x(), -deltaPos.y());
    }

    update();

}
