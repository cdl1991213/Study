#include "cdlopenglwidget.h"

unsigned int VAO, VBO, lightVAO;
QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);     //光源
QVector3D objectColor(1.0f, 0.5f, 0.31f);

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
    QVector3D(0.0f, 0.0f, 0.0f),
    QVector3D(2.0f, 5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D(2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f, 3.0f, -7.5f),
    QVector3D(1.3f, -2.0f, -2.5f),
    QVector3D(1.5f, 2.0f, -2.5f),
    QVector3D(1.5f, 0.2f, -1.5f),
    QVector3D(-1.3f, 0.2f, -1.5f),
};

const unsigned int timeOutSec = 50;
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    timer.start(timeOutSec);    //计时器
    time.start();               //时刻

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
//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    ShaderProgram.bind();
    //光照
    ShaderProgram.setUniformValue("objectColor", objectColor);
    ShaderProgram.setUniformValue("lightColor", lightColor);
    ShaderProgram.setUniformValue("lightPos", lightPos);
    ShaderProgram.setUniformValue("viewPos", camera.Position);
    //--------------------------------------------------------------------------------------------------
    //############################################着色器ShaderProgram_light##############################
    //--------------------------------------------------------------------------------------------------
    bool success_light;   //是否成功
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_light.vert");
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_light.frag");
    success_light = ShaderProgram_light.link();
//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    ShaderProgram_light.bind();
    //光照
    ShaderProgram_light.setUniformValue("lightColor", lightColor);

    //--------------------------------------------------------------------------------------------------
    //############################################纹理库#################################################
    //--------------------------------------------------------------------------------------------------


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
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 model;   //3D变换矩阵    物体对象
    QMatrix4x4 view;    //3D观察矩阵    摄像机
    QMatrix4x4 projection;      //3D投影矩阵    画布投影
//    unsigned int time = QTime::currentTime().msec();
    float time1 = time.elapsed()/5.0;

    //----------OpenGL对象---------
    glBindVertexArray(VAO);
    //-----------着色器------------
    ShaderProgram.bind();
    //------------3D矩阵-----------
    //view
    view = camera.GetViewMatrix();
//    view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
    ShaderProgram.setUniformValue("view", view);
    //projection
    projection.perspective(camera.Zoom, (float)width()/(float)height(), 0.1, 100);
    ShaderProgram.setUniformValue("projection", projection);
    //model
    model.rotate(time1/10, 1.0f, 5.0f, 0.5f);   //旋转矩阵，绕y轴旋转
    ShaderProgram.setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER

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
    model.translate(lightPos);
    //rotate(旋转角度, x轴, y轴, z轴)
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);   //旋转矩阵，绕y轴旋转
    model.scale(0.2);
    ShaderProgram_light.setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER




}


//---------------------------------------------------------------------------------------------------------------------------
void cdlOpenGLWidget::on_timeout()
{
    update();   //重新执行paintGL()
}
//----------------------------------------------------camera class-----------------------------------------------------------
