#include "cdlopenglwidget.h"

unsigned int VAO, VBO, EBO;

float vertices_rectangle_ebo[] = {  //借助EBO
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   //右上
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  //右下
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //左下
    -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f,  //左上
};
//ebo索引，记录不重复顶点
unsigned int indices[] = {
    //第一个三角形
    0, 1, 3,
    //第二个三角形
    1, 2, 3,
};

//cdlopenglwidget的构造函数
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

//cdlopenglwidget的析构函数
cdlOpenGLWidget::~cdlOpenGLWidget()
{
    makeCurrent();  //调出当前状态
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    doneCurrent();  //退出当前状态

}

//------------------------------------------toolbar--------------------------------------------------
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


//------------------------------------------主程序--------------------------------------------------
void cdlOpenGLWidget::initializeGL()
{
    //初始化
    initializeOpenGLFunctions();

    //--------------------------------------------------------------------------------------------------
    //############################################着色器##################################################
    //--------------------------------------------------------------------------------------------------
    bool success;   //是否成功
//    myShaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
//    myShaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    myShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shapes.vert");
    myShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shapes.frag");
    success = myShaderProgram.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    myShaderProgram.bind();
    myShaderProgram.setUniformValue("xOffset", 0.4f);   //给予偏移量
    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //------------------------VAO1----------------------------
    glBindVertexArray(VAO);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectangle_ebo), vertices_rectangle_ebo, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //...在此传入ShaderProgram
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //...在此传入ShaderProgram
    //EBO部分
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //EBO中的总数据大小应与VBO中对应
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);     //借助EBO画矩形时，不能释放GL_ELEMENT_ARRAY_BUFFER

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //-------------------------------------------------------
    //--------------------------------------------------------------------------------------------------

}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    //暂时先不用的参数
    Q_UNUSED(w);Q_UNUSED(h);

}

void cdlOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);//设置widget背景颜色
    glClear(GL_COLOR_BUFFER_BIT);//使用widget背景颜色

    //画图的时候使用myShaderProgram
    myShaderProgram.bind();

    glBindVertexArray(VAO);

    switch (myShape) {
    case Rect:
        //借助EBO，画矩形
        glDrawElements(GL_TRIANGLES, 3 , GL_UNSIGNED_INT, 0);
        //希望不借助EBO，仅依靠indices数据画矩形
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);
        break;
    case None:
        //什么都不干
        break;
    default:
        break;
    }



}
