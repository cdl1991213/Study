#include "cdlopenglwidget.h"

unsigned int VAO, VBO;

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
cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    time.start();
    timer.start(TIMEOUTMSEC);
    //(发出信号的对象A， 对象A的信号， 接收信号的对象B， 需要调用的对象B的函数)
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

//    camera.Position = QVector3D(0, 0, 3.0);  //camera放在z=3
}

cdlOpenGLWidget::~cdlOpenGLWidget()
{
    if(isValid()){return;}  //程序对象初始化发生错误（如initializeGL(),resizeGL(),paintGL()）

    makeCurrent();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    doneCurrent();

}


//----------------------------------------------------主程序------------------------------------------------------------------

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
    //纹理图案
    ShaderProgram.bind();
    ShaderProgram.setUniformValue("PandaLisa", 0);      //通道0
    ShaderProgram.setUniformValue("Wood", 1);         //通道1

    //--------------------------------------------------------------------------------------------------
    //############################################纹理库#################################################
    //--------------------------------------------------------------------------------------------------
    //纹理效果————背景为透明image.png不自动填充背景色
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //纹理库
    PandaLisa = new QOpenGLTexture(QImage(":/texture/images/PandaLisa.jpg").mirrored());
    Wood = new QOpenGLTexture(QImage(":/texture/images/wood.png").mirrored());
    PandaLisa -> bind(0);
    Wood -> bind(1);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //texture attribute_location = 2
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //-------------------------------------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //--------------------------------------------------------------------------------------------------
    //##################################################################################################
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

    unsigned int time = QTime::currentTime().msec();
    QMatrix4x4 model;   //3D变换矩阵    物体对象
    QMatrix4x4 view;    //3D观察矩阵    摄像机
    QMatrix4x4 projection;      //3D投影矩阵    画布投影

    if(true){
        //-----------着色器------------
        ShaderProgram.bind();
        //----------OpenGL对象---------
        glBindVertexArray(VAO);
        //------------纹理变换----------
        PandaLisa -> bind(0);
        Wood -> bind(1);
        //------------3D矩阵-----------
        //view
        view = camera.GetViewMatrix();
    //        view.lookAt(camera_3D.Position, camera_3D.Position + camera_3D.Front, camera_3D.Up);
    //        view.lookAt(QVector3D(camX, 0.0, camZ), cameraTarget, up);    //旋转木马效果
    //        view.lookAt(cameraPos, cameraTarget, up);
        view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
        ShaderProgram.setUniformValue("view", view);
        //projection
        projection.perspective(camera.Zoom, (float)width()/(float)height(), 0.1, 100);
        ShaderProgram.setUniformValue("projection", projection);
        //model
        foreach(auto item, cubePosition){
            model.setToIdentity();
            model.translate(item);
            model.rotate(time/10, 0.0f, 1.0f, 0.0f);   //旋转矩阵，绕y轴旋转
            ShaderProgram.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);   //GL_ARRAY_BUFFER
        }
    }

}
//---------------------------------------------------------------------------------------------------------------------------
void cdlOpenGLWidget::on_timeout()
{
    update();   //重新执行paintGL()
}

//----------------------------------------------------camera class-----------------------------------------------------------
void cdlOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    float deltaTime = TIMEOUTMSEC / 1000.0;
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
    default:
        break;
    }
    update();
}

QPoint deltaPos;
void cdlOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastPos(width()/2, height()/2);
    auto currentPos = event -> pos();
    deltaPos = currentPos - lastPos;
    lastPos = currentPos;

    camera.ProcessMouseMovement(deltaPos.x(), -deltaPos.y());

    update();

}


void cdlOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    camera.ProcessMouseScroll(event -> angleDelta().y()/120);

    update();
}
