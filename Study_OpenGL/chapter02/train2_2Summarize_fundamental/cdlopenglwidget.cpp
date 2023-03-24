#include "cdlopenglwidget.h"

unsigned int VAO, VBO_TRIANGLE, VBO_RECTANGLE, EBO;

float vertices_triangle[] = {
    -0.9f, -0.5f, 0.0f,     //第一个顶点的x,y,z坐标
    -0.0f, -0.5f, 0.0f,      //第二个顶点的x,y,z坐标
    -0.45f, 0.5f, 0.0f,        //第三个顶点的x,y,z坐标
};

float vertices_rectangle_ebo[] = {  //借助EBO
    0.0f, -0.5f, 0.0f,   //左下
    0.0f, 0.5f, 0.0f,  //左上
    0.9f, 0.5f, 0.0f, //右上
    0.9f, -0.5f, 0.0f,  //右下
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

}

//cdlopenglwidget的析构函数
cdlOpenGLWidget::~cdlOpenGLWidget()
{
    makeCurrent();  //调出当前状态
    glDeleteBuffers(1, &VBO_TRIANGLE);
    glDeleteBuffers(1, &VBO_RECTANGLE);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    doneCurrent();  //退出当前状态

}
//-------------------------------------------------------------toolbar-------------------------------------------------------


//--------------------------------------------------------------主程序--------------------------------------------------------
void cdlOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();    //初始化

    //--------------------------------------------------------------------------------------------------
    //############################################着色器##################################################
    //--------------------------------------------------------------------------------------------------
    bool success;   //是否成功
    myShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders.vert");    //读取顶点着色器资源文件
    myShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders.frag");  //读取片段着色器资源文件
    success = myShaderProgram.link();
//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    //1.创建对象
    //参数(需要创建的缓存数量，ID)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_TRIANGLE);
    glGenBuffers(1, &VBO_RECTANGLE);
    glGenBuffers(1, &EBO);

    //2.绑定对象
    glBindVertexArray(VAO);     //绑定VAO,所有跟GL_ARRAY_BUFFER有关的操作都会被记录

    //########绑定VBO_TRIANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);    //绑定当前操作的对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);    //创建vertices大小的数据存储
    //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);   //解析属性（数据的大小、位置）,将数据传递到gpu缓存

    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectangle_ebo), vertices_rectangle_ebo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //EBO部分
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //3.启用属性
    glEnableVertexAttribArray(0);   //开启VAO中的第一个属性

    //4.绑定空缓冲区，达到释放对象的效果
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);    //暂时先不用的参数防止弹出警告
    Q_UNUSED(h);
}

void cdlOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);//设置widget背景颜色
    glClear(GL_COLOR_BUFFER_BIT);//使用widget背景颜色

    myShaderProgram.bind();     //使用着色器

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);   //画三角形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //借助EBO，画矩形
}
