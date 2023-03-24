#include "cdlopenglwidget.h"

unsigned int VAOs[4], VBO_TRIANGLE, VBO_RECTANGLE, VBO_RECTANGLE_TEXTURE, VBO_RECTANGLE_3D, EBO;

float vertices_triangle[] = {
    -0.3f, -0.3f, 0.0f,     //左下
    0.3f, -0.3f, 0.0f,     //右下
    0.0f, 0.3f, 0.0f,     //上
};

float vertices_rectriangle_ebo[] = {  //借助EBO
                        //position              //color
                        0.3f, 0.3f, 0.0f,       1.0f, 0.0f, 0.0f,   //右上
                        0.3f, -0.3f, 0.0f,      0.0f, 1.0f, 0.0f,   //右下
                        -0.3f, -0.3f, 0.0f,     0.0f, 0.0f, 1.0f,   //左下
                        -0.3f, 0.3f, 0.0f,      0.5f, 0.5f, 0.5f,   //左上
                     };

unsigned int indices[] = {  //ebo索引，记录不重复顶点
    //第一个三角形
    0, 1, 3,
    //第二个三角形
    1, 2, 3
};

float vertices_rectriangle_ebo_texture[] = {  //借助EBO
                        //position              //color             //texturePosition
                        0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,   1.2f, 1.2f,   //右上
                        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.2f, 0.0f,  //右下
                        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, //左下
                        -0.5f, 0.5f, 0.0f,      0.5f, 0.5f, 0.5f,   0.0f, 1.2f,  //左上
                     };

float vertices_rectriangle_ebo_3D[] = {  //借助EBO
                                         //position                     //texturePosition
                                         -0.9f, -0.9f, -0.9f,           0.0f, 0.0f,
                                         0.9f, -0.9f, -0.9f,            1.0f, 0.0f,
                                         0.9f, 0.9f, -0.9f,             1.0f, 1.0f,
                                         0.9f, 0.9f, -0.9f,             1.0f, 1.0f,
                                         -0.9f, 0.9f, -0.9f,            0.0f, 1.0f,
                                         -0.9f, -0.9f, -0.9f,           0.0f, 0.0f,

                                         -0.9f, -0.9f, 0.9f,            0.0f, 0.0f,
                                         0.9f, -0.9f, 0.9f,             1.0f, 0.0f,
                                         0.9f, 0.9f, 0.9f,              1.0f, 1.0f,
                                         0.9f, 0.9f, 0.9f,              1.0f, 1.0f,
                                         -0.9f, 0.9f, 0.9f,             0.0f, 1.0f,
                                         -0.9f, -0.9f, 0.9f,            0.0f, 0.0f,

                                         -0.9f, 0.9f, 0.9f,             1.0f, 0.0f,
                                         -0.9f, 0.9f, -0.9f,            1.0f, 1.0f,
                                         -0.9f, -0.9f, -0.9f,           0.0f, 1.0f,
                                         -0.9f, -0.9f, -0.9f,           0.0f, 1.0f,
                                         -0.9f, -0.9f, 0.9f,            0.0f, 0.0f,
                                         -0.9f, 0.9f, 0.9f,             1.0f, 0.0f,

                                         0.9f, 0.9f, 0.9f,              1.0f, 0.0f,
                                         0.9f, 0.9f, -0.9f,             1.0f, 1.0f,
                                         0.9f, -0.9f, -0.9f,            0.0f, 1.0f,
                                         0.9f, -0.9f, -0.9f,            0.0f, 1.0f,
                                         0.9f, -0.9f, 0.9f,             0.0f, 0.0f,
                                         0.9f, 0.9f, 0.9f,              1.0f, 0.0f,

                                         -0.9f, -0.9f, -0.9f,           0.0f, 1.0f,
                                         0.9f, -0.9f, -0.9f,            1.0f, 1.0f,
                                         0.9f, -0.9f, 0.9f,             1.0f, 0.0f,
                                         0.9f, -0.9f, 0.9f,             1.0f, 0.0f,
                                         -0.9f, -0.9f, 0.9f,            0.0f, 0.0f,
                                         -0.9f, -0.9f, -0.9f,           0.0f, 1.0f,

                                         -0.9f, 0.9f, -0.9f,            0.0f, 1.0f,
                                         0.9f, 0.9f, -0.9f,             1.0f, 1.0f,
                                         0.9f, 0.9f, 0.9f,              1.0f, 0.0f,
                                         0.9f, 0.9f, 0.9f,              1.0f, 0.0f,
                                         -0.9f, 0.9f, 0.9f,             0.0f, 0.0f,
                                         -0.9f, 0.9f, -0.9f,            0.0f, 1.0f,
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

#define TIMEOUTMSEC 100
QPoint deltaPos;
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer.start(TIMEOUTMSEC);
    time_3D.start();
    //信号槽机制slot -> signal
    //(发出信号的对象A， 对象A的信号， 接收信号的对象B， 需要调用的对象B的函数)
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    camera_3D.Position = QVector3D(0, 0, 3.0);  //camera放在z=3
}

cdlOpenGLWidget::~cdlOpenGLWidget()
{
    if(isValid()){return;}  //程序对象初始化发生错误（如initializeGL(),resizeGL(),paintGL()）

    makeCurrent();  //调出当前状态
    glDeleteBuffers(1, &VBO_TRIANGLE);
    glDeleteBuffers(1, &VBO_RECTANGLE);
    glDeleteBuffers(1, &VBO_RECTANGLE_TEXTURE);
    glDeleteBuffers(1, &VBO_RECTANGLE_3D);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(4, VAOs);
    doneCurrent();  //退出当前状态

}

//-------------------------------------------------------------toolbar-------------------------------------------------------
//画图
void cdlOpenGLWidget::drawShape(cdlOpenGLWidget::Shape shape)
{
    myShape = shape;
    update();   //清空widget,重新触发paintGL()
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
float borderColor_1[] = { 1.0f, 1.0f, 0.0f, 1.0f };   //纹理效果背景颜色
float borderColor_2[] = { 1.0f, 0.0f, 1.0f, 1.0f };   //纹理效果背景颜色
float ratio = 0.5;

void cdlOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //--------------------------------------------------------------------------------------------------
    //############################################纹理库#################################################
    //--------------------------------------------------------------------------------------------------
    //背景为透明image.png不自动填充背景色
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //纹理
    PandaLisa = new QOpenGLTexture(QImage(":/texture/images/PandaLisa.jpg").mirrored());
    rabbit = new QOpenGLTexture(QImage(":/texture/images/rabbit.png").mirrored());
    //---------------------纹理效果
    /*
     * GL_TEXTURE_WRAP_S    x轴
     * GL_TEXTURE_WRAP_T    y轴
     *
     * GL_REPEAT
     * GL_MIRRORED_REPEAT
     * GL_CLAMP_TO_EDGE
     * GL_CLAMP_TO_BORDER
    */

    //---------------------纹理过滤
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
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);        //纹理过滤(适用于缩小)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         //纹理过滤（适用于放大）
    PandaLisa -> bind(0);
    //---------------------纹理效果(通道0)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor_1);
    //---------------------纹理过滤(通道0)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);        //纹理过滤(适用于缩小)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         //纹理过滤（适用于放大）
    rabbit -> bind(1);
    //---------------------纹理效果(通道1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor_2);
    //---------------------纹理过滤(通道1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);        //纹理过滤(适用于缩小)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         //纹理过滤（适用于放大）
    //--------------------------------------------------------------------------------------------------
    //############################################着色器ShaderProgram_fundamental########################
    //--------------------------------------------------------------------------------------------------
    bool success_fundamental;   //是否成功
    ShaderProgram_fundamental.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_fundamental.vert");
    ShaderProgram_fundamental.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_fundamental.frag");
    success_fundamental = ShaderProgram_fundamental.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    //--------------------------------------------------------------------------------------------------
    //############################################着色器ShaderProgram_texture############################
    //--------------------------------------------------------------------------------------------------
    bool success_texture;   //是否成功
    ShaderProgram_texture.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_texture.vert");
    ShaderProgram_texture.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_texture.frag");
    success_texture = ShaderProgram_texture.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    //纹理图案
    ShaderProgram_texture.bind();
    ShaderProgram_texture.setUniformValue("PandaLisa", 0);      //通道0
    ShaderProgram_texture.setUniformValue("rabbit", 1);         //通道1
    PandaLisa -> generateMipMaps();     //多级渐远纹理

    //--------------------------------------------------------------------------------------------------
    //#####################################着色器ShaderProgram_texture_manual############################
    //--------------------------------------------------------------------------------------------------
    bool success_texture_manual;   //是否成功
    ShaderProgram_texture_manual.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_texture_manual.vert");
    ShaderProgram_texture_manual.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_texture_manual.frag");
    success_texture_manual = ShaderProgram_texture.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    //纹理图案
    ShaderProgram_texture_manual.bind();
    ShaderProgram_texture_manual.setUniformValue("PandaLisa", 0);      //通道0
    ShaderProgram_texture_manual.setUniformValue("rabbit", 1);         //通道1
    ShaderProgram_texture_manual.setUniformValue("ratio", ratio);       //ratio初始值
    PandaLisa -> generateMipMaps();     //多级渐远纹理
    //--------------------------------------------------------------------------------------------------
    //#####################################着色器ShaderProgram_3D########################################
    //--------------------------------------------------------------------------------------------------
    bool success_3D;   //是否成功
    ShaderProgram_3D.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader_3D.vert");
    ShaderProgram_3D.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader_3D.frag");
    success_3D = ShaderProgram_3D.link();

//    if(!success){
//        qDebug()<<"ERR:"<<myShaderProgram.log();
//    }

    //纹理图案
    ShaderProgram_3D.bind();
    ShaderProgram_3D.setUniformValue("PandaLisa", 0);      //通道0
    ShaderProgram_3D.setUniformValue("rabbit", 1);         //通道1
    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    glGenVertexArrays(4, VAOs);

    glGenBuffers(1, &VBO_TRIANGLE);
    glGenBuffers(1, &VBO_RECTANGLE);
    glGenBuffers(1, &VBO_RECTANGLE_TEXTURE);
    glGenBuffers(1, &VBO_RECTANGLE_3D);
    glGenBuffers(1, &EBO);

    //-------------------------------------VAOs[0]-----------------------------------
    glBindVertexArray(VAOs[0]);
    //########绑定VBO_TRIANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
    //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //-------------------------------------VAOs[1]-----------------------------------
    glBindVertexArray(VAOs[1]);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_ebo), vertices_rectriangle_ebo, GL_STATIC_DRAW);
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //color attribute_location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //#################EBO###################
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //-------------------------------------VAOs[2]-----------------------------------
    glBindVertexArray(VAOs[2]);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE_TEXTURE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_ebo_texture), vertices_rectriangle_ebo_texture, GL_STATIC_DRAW);
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //color attribute_location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute_location = 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //#################EBO###################
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //-------------------------------------VAOs[3]-----------------------------------
    glBindVertexArray(VAOs[3]);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE_3D);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_ebo_3D), vertices_rectriangle_ebo_3D, GL_STATIC_DRAW);
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //texture attribute_location = 2
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
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

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    QMatrix4x4 matrix;  //2D变换矩阵
    unsigned int time = QTime::currentTime().msec();
    int i = 0;
    QMatrix4x4 model;   //3D变换矩阵
    QMatrix4x4 view;    //3D观察矩阵
    QMatrix4x4 projection;      //3D投影矩阵
    /*
     * (画布大小, (float)width()/(float)height(), 镜头离物体距离, 镜头离画布距离)
     * 画布大小：数值越大，对象越显小
    */


//    const float radius = 10.0f;
//    float time_radius = time_3D.elapsed()/1000.0;
//    float camX = sin(time_radius) * radius;
//    float camZ = cos(time_radius) * radius;


    switch (myShape) {
    case Triangle:
        //-----------着色器------------
        ShaderProgram_fundamental.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   //GL_ARRAY_BUFFER
        break;
    case Rect:
        //-----------着色器------------
        ShaderProgram_fundamental.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //GL_ELEMENT_ARRAY_BUFFER
        break;
    case Rect_Tecture:
        //-----------着色器------------
        ShaderProgram_texture.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[2]);
        //------------纹理效果----------
        PandaLisa -> bind(0);
        rabbit -> bind(1);
        //##############Element1##############
        //------------矩阵变换----------
        matrix.translate(0.3, -0.3, 0);             //位移矩阵
        matrix.rotate(time, 0.0f, 0.0f, 1.0f);      //旋转矩阵，绕z轴旋转
        ShaderProgram_texture.setUniformValue("Matrix", matrix);   //变换矩阵
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //GL_ELEMENT_ARRAY_BUFFER
        //##############Element2##############
        //------------矩阵变换----------
        matrix.setToIdentity();     //恢复起点
        matrix.translate(-0.5, 0.5, 0);     //位移矩阵
        matrix.scale(fabs(sin(time)));      //缩放矩阵
        ShaderProgram_texture.setUniformValue("Matrix", matrix);   //变换矩阵
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        break;
    case Rect_Tecture_ManualDynamic:
        //-----------着色器------------
        ShaderProgram_texture_manual.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[2]);
        //------------纹理变换----------
        PandaLisa -> bind(0);
        rabbit -> bind(1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //GL_ELEMENT_ARRAY_BUFFER
        break;
    case ThreeD:
        //-----------着色器------------
        ShaderProgram_3D.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[3]);
        //------------纹理变换----------
        PandaLisa -> bind(0);
        rabbit -> bind(1);
        //------------3D矩阵-----------
        /*
         * view         摄像机
         * model        物体对象
         * projection   画布投影
        */
        //view
        glViewport(0, 0, width(), height());
        view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
        ShaderProgram_3D.setUniformValue("view", view);
        //projection
        projection.perspective(camera_3D.Zoom, (float)width()/(float)height(), 0.1, 100);
        ShaderProgram_3D.setUniformValue("projection", projection);
        //model
        foreach(auto item, cubePosition){
            model.setToIdentity();
            model.translate(item);
            if(i++ % 3 == 0){
                model.rotate(time/10, 0.0f, 1.0f, 0.0f);   //旋转矩阵，绕y轴旋转
            }
            ShaderProgram_3D.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER
        }
        break;
    case ThreeD_Rotate:
        //-----------着色器------------
        ShaderProgram_3D.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[3]);
        //------------纹理变换----------
        PandaLisa -> bind(0);
        rabbit -> bind(1);
        //------------3D矩阵-----------
        //view
        view = camera_3D.GetViewMatrix();
//        view.lookAt(camera_3D.Position, camera_3D.Position + camera_3D.Front, camera_3D.Up);
//        view.lookAt(QVector3D(camX, 0.0, camZ), cameraTarget, up);    //旋转木马效果
//        view.lookAt(cameraPos, cameraTarget, up);
        view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
        ShaderProgram_3D.setUniformValue("view", view);
        //projection
        projection.perspective(camera_3D.Zoom, (float)width()/(float)height(), 0.1, 100);
        ShaderProgram_3D.setUniformValue("projection", projection);
        //model
        foreach(auto item, cubePosition){
            model.setToIdentity();
            model.translate(item);
            model.rotate(time/10, 0.0f, 1.0f, 0.0f);   //旋转矩阵，绕y轴旋转
            ShaderProgram_3D.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER
        }
        break;
    case None:
        //什么都不干
        break;
    default:
        break;
    }

}
//---------------------------------------------------------------------------------------------------------------------------
void cdlOpenGLWidget::on_timeout()
{
    update();   //重新执行paintGL()
}

void cdlOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
//    float cameraSpeed = 2.5 * TIMEOUTMSEC / 1000;
    float deltaTime = TIMEOUTMSEC / 1000.0;
    switch (event -> key()) {
    //↑↓图片渐变
    case Qt::Key_Up:
        ratio+=0.1;
        break;
    case Qt::Key_Down:
        ratio-=0.1;
        break;
    //wasd移动camera
    case Qt::Key_W:
        camera_3D.ProcessKeyboard(FORWARD, deltaTime);
        break;
    case Qt::Key_S:
        camera_3D.ProcessKeyboard(BACKWARD, deltaTime);
        break;
    case Qt::Key_A:
        camera_3D.ProcessKeyboard(RIGHT, deltaTime);
        break;
    case Qt::Key_D:
        camera_3D.ProcessKeyboard(LEFT, deltaTime);
        break;
    default:
        break;
    }

    if(ratio > 1){ratio = 1;}
    if(ratio < 0){ratio = 0;}

    ShaderProgram_texture_manual.bind();
    ShaderProgram_texture_manual.setUniformValue("ratio", ratio);


    update();
}


void cdlOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{

    static QPoint lastPos(width()/2, height()/2);
    auto currentPos = event -> pos();
    deltaPos = currentPos - lastPos;
    lastPos = currentPos;

    camera_3D.ProcessMouseMovement(deltaPos.x(), -deltaPos.y());

    update();
}


void cdlOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    camera_3D.ProcessMouseScroll(event -> angleDelta().y()/120);

    update();
}
