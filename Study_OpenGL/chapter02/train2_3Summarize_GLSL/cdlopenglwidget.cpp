#include "cdlopenglwidget.h"

unsigned int VAOs[2], VBO_TRIANGLE, VBO_RECTANGLE, EBO;

float vertices_triangle[] = {
    -0.9f, -0.5f, 0.0f,
    -0.0f, -0.5f, 0.0f,
    -0.45f, 0.5f, 0.0f,
};

float vertices_rectangle_ebo[] = {  //借助EBO
    0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   //左下
    0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   //左上
    0.9f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   //右上
    0.9f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f,  //右下
};
//ebo索引，记录不重复顶点
unsigned int indices[] = {
    //第一个三角形
    0, 1, 3,
    //第二个三角形
    1, 2, 3
};

//cdlopenglwidget的构造函数
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    myTimer.start(100);
    //(发出信号的对象A， 对象A的信号， 接收信号的对象B， 需要调用的对象B的函数)
    connect(&myTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));     //信号槽机制slot -> signal
}

//cdlopenglwidget的析构函数
cdlOpenGLWidget::~cdlOpenGLWidget()
{
    if(isValid()){return;}  //程序对象初始化发生错误（如initializeGL(),resizeGL(),paintGL()）

    makeCurrent();
    glDeleteBuffers(1, &VBO_TRIANGLE);
    glDeleteBuffers(1, &VBO_RECTANGLE);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(2, VAOs);
    doneCurrent();

}
//-------------------------------------------------------------toolbar-------------------------------------------------------
//画图
void cdlOpenGLWidget::drawShape(cdlOpenGLWidget::Shape shape)
{
    myShape = shape;
    update();   //在paintGL()外重新触发绘制（即清空widget，重新绘制），需要调用update()更新widget
}

//线框模式
void cdlOpenGLWidget::setWireMode(bool mode)
{
    makeCurrent();
    if(mode)
        //线条绘制Polygon
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        //填充绘制Polygon
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    update();
    doneCurrent();
}

//--------------------------------------------------------------主程序--------------------------------------------------------
void cdlOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();    //初始化

    //--------------------------------------------------------------------------------------------------
    //############################################着色器1--tirangle######################################
    //--------------------------------------------------------------------------------------------------
    bool success1;   //是否成功
    myShaderProgram1.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders1.vert");
    myShaderProgram1.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders1.frag");
    success1 = myShaderProgram1.link();
//    if(!success1){
//        qDebug()<<"ERR:"<<myShaderProgram1.log();
//    }

    //-----------------------------layout---------------------------
    //    //查找aPos在CPU中的位置
    //    myShaderProgram.bind();
    //    GLint posLocation = myShaderProgram.attributeLocation("aPos");

        //设置aPos在CPU中的位置
        myShaderProgram1.bind();
        GLint posLocation = 2;
        myShaderProgram1.bindAttributeLocation("aPos", posLocation);
    //--------------------------------------------------------------------------------------------------
    //############################################着色器2--rect##########################################
    //--------------------------------------------------------------------------------------------------
    bool success2;   //是否成功
    myShaderProgram2.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders2.vert");
    myShaderProgram2.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders2.frag");
    success2 = myShaderProgram2.link();
//    if(!success2){
//        qDebug()<<"ERR:"<<myShaderProgram2.log();
//    }

    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    //参数(需要创建的缓存数量，ID)
    glGenVertexArrays(2, VAOs);
    glGenBuffers(1, &VBO_TRIANGLE);
    glGenBuffers(1, &VBO_RECTANGLE);
    glGenBuffers(1, &EBO);

    //-------------------------------------VAOs[0]-----------------------------------
    glBindVertexArray(VAOs[0]);

    //########绑定VBO_TRIANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
    //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(posLocation);
    //-------------------------------------VAOs[1]-----------------------------------
    glBindVertexArray(VAOs[1]);

    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectangle_ebo), vertices_rectangle_ebo, GL_STATIC_DRAW);
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //color attribute_location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //EBO部分
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void cdlOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    switch (myShape) {
    case Rect:
        myShaderProgram2.bind();
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //借助EBO，画矩形
        break;
    case Triangle:
        myShaderProgram1.bind();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   //画三角形
        break;
    case None:
        //什么都不干
        break;
    default:
        break;
    }

}

#include <QTime>
#include <math.h>
void cdlOpenGLWidget::on_timeout()
{
    if(myShape == None){return;}    //如果选择清空图形，不需要运行该进程

    makeCurrent();
    int timeValue = QTime::currentTime().second();
    float greenValue = (sin(timeValue) / 2.0f) +0.5f;
    myShaderProgram1.setUniformValue("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
    update();
    doneCurrent();
}
