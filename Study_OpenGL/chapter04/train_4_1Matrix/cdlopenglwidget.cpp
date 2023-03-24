#include "cdlopenglwidget.h"
#include "math.h"

unsigned int VAO, VBO, EBO;

float vertices[] = {  //借助EBO
                        //position              //color             //texturePosition
                        0.3f, 0.3f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   //右上
                        0.3f, -0.3f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  //右下
                        -0.3f, -0.3f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, //左下
                        -0.3f, 0.3f, 0.0f,      0.5f, 0.5f, 0.5f,   0.0f, 1.0f,  //左上
                     };

//ebo索引，记录不重复顶点
unsigned int indices[] = {
    //第一个三角形
    0, 1, 3,
    //第二个三角形
    1, 2, 3,
};

float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };


//cdlopenglwidget的构造函数
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer.start(100);
    //信号槽机制slot -> signal
    //(发出信号的对象A， 对象A的信号， 接收信号的对象B， 需要调用的对象B的函数)
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Bluetexture = new QOpenGLTexture(QImage(":/image/texture_image/blueTexture.jpg").mirrored());       //纹理器0
    Goldtexture = new QOpenGLTexture(QImage(":/image/texture_image/goldTexture.jpg").mirrored());       //纹理器1
    //------------------------样式1----------------------------
    bool success1;   //是否成功
    myShaderProgram1.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shapes1.vert");
    myShaderProgram1.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shapes1.frag");
    success1 = myShaderProgram1.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    myShaderProgram1.bind();
    myShaderProgram1.setUniformValue("textureBlue", 0);     //通道0
    myShaderProgram1.setUniformValue("textureGold", 1);     //通道1
    Bluetexture -> generateMipMaps();     //多级渐远纹理
    //--------纹理1-------
    Bluetexture -> bind(0);     //绑定 纹理0 至 myShaderProgram1 的 通道0-->对应textureBlue, myShaderProgram1可以通过uniform获取对应textureBlue
    /*
     * GL_TEXTURE_MIN_FILTER 缩小的时候
     *      //纹理过滤参数
     *      GL_NEAREST
     *      GL_LINEAR
     *      //多级渐远纹理参数
     *      GL_NEAREST_MIPMAP_NEAREST
     *      GL_LINEAR_MIPMAP_NEAREST
     *      GL_NEAREST_MIPMAP_LINEAR
     *      GL_LINEAR_MIPMAP_LINEAR
     *
     * GL_TEXTURE_MAG_FILTER 放大的时候
     *      GL_NEAREST
     *      GL_LINEAR
    */
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);      //纹理过滤(适用于缩小)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);      //纹理过滤（适用于放大）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //--------纹理2-------
    Goldtexture -> bind(1);     //绑定 纹理1 至 myShaderProgram1 的 通道1-->对应textureGold, myShaderProgram1可以通过uniform获取对应textureGold
//    matrix.translate(0.05, -0.05, 0);
    //------------------------样式2----------------------------
    bool success2;   //是否成功
    myShaderProgram2.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shapes2.vert");
    myShaderProgram2.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shapes2.frag");
    success2 = myShaderProgram2.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    myShaderProgram2.bind();
    myShaderProgram2.setUniformValue("textureBlue", 0);     //通道0
    myShaderProgram2.setUniformValue("textureGold", 1);     //通道1
    //-------纹理1--------
    Bluetexture -> bind(0);     //绑定 纹理0 至 myShaderProgram2 的 通道0-->对应textureBlue, myShaderProgram2可以通过uniform获取对应textureBlue
    //-------纹理2--------
    Goldtexture -> bind(1);     //绑定 纹理1 至 myShaderProgram2 的 通道1-->对应textureGold, myShaderProgram2可以通过uniform获取对应textureGold
    /*
     * GL_TEXTURE_WRAP_S    x轴
     * GL_TEXTURE_WRAP_T    y轴
     *
     * GL_REPEAT
     * GL_MIRRORED_REPEAT
     * GL_CLAMP_TO_EDGE
     * GL_CLAMP_TO_BORDER
    */
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);      //在bind(0)下面，所以只对纹理0起作用
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);      //在bind(1)下面，所以只对纹理1起作用
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //------------------------VAOs[0]----------------------------
    glBindVertexArray(VAO);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //EBO部分
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);   //EBO中的总数据大小应与VBO中对应
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

    QMatrix4x4 matrix;  //每次update()初始化矩阵
    unsigned int time = QTime::currentTime().msec();
    matrix.translate(0.5, -0.5, 0);
    matrix.rotate(time, 0.0f, 0.0f, 1.0f);

    switch (myShape) {
    case Rect:
        myShaderProgram1.bind();
        glBindVertexArray(VAO);
        Bluetexture -> bind(0);
        Goldtexture -> bind(1);
        myShaderProgram1.setUniformValue("myMatrix", matrix);   //旋转矩阵
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        matrix.setToIdentity();     //恢复起点
        matrix.translate(-0.5, 0.5, 0);
        matrix.scale(fabs(sin(time)));
        myShaderProgram1.setUniformValue("myMatrix", matrix);   //旋转矩阵
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        break;
    case None:
        //什么都不干
        break;
    default:
        break;
    }



}

void cdlOpenGLWidget::on_timeout()
{
    update();   //重新执行paintGL()
}
