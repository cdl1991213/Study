#include "cdlopenglwidget.h"

unsigned int VAOs[4], lightVAO;
unsigned int VBO_TRIANGLE, VBO_RECTANGLE_1, VBO_RECTANGLE_2, EBO, VBO_ThreeD_1;
QVector3D lightPos(1.2f, 1.0f, 2.0f);       //光源位置
QVector3D lightColor(1.0f, 1.0f, 1.0f);     //光源颜色
QVector3D viewInitPos(0.0, 0.0, 5.0);       //初始摄像机位置
const float PI=3.1415926;

float vertices_triangle[] = {
    -0.3f, -0.3f, 0.0f,     0.0f, 0.0f, 1.0f,//左下
    0.3f, -0.3f, 0.0f,      0.0f, 1.0f, 0.0f,//右下
    0.0f, 0.3f, 0.0f,       1.0f, 0.0f, 0.0f,//上
};

float vertices_rectriangle_ebo[] = {  //借助EBO
                        //position              //color
                        0.3f, 0.3f, 0.0f,       1.0f, 0.0f, 0.0f,   //右上
                        0.3f, -0.3f, 0.0f,      0.0f, 1.0f, 0.0f,   //右下
                        -0.3f, -0.3f, 0.0f,     0.0f, 0.0f, 1.0f,   //左下
                        -0.3f, 0.3f, 0.0f,      0.5f, 0.5f, 0.5f,   //左上
                     };
float vertices_rectriangle_texture_ebo[] = {  //借助EBO
                                              //position              //color             //texturePosition
                                              0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,   1.2f, 1.2f,   //右上
                                              0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.2f, 0.0f,  //右下
                                              -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, //左下
                                              -0.5f, 0.5f, 0.0f,      0.5f, 0.5f, 0.5f,   0.0f, 1.2f,  //左上
                                           };
unsigned int indices_rectriangle[] = {  //ebo索引，记录不重复顶点
                                        //第一个三角形
                                        0, 1, 3,
                                        //第二个三角形
                                        1, 2, 3
                                     };

float vertices_ThreeD_1[] = {
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

    Camera.Position = QVector3D(0, 0, 5.0);  //初始化camera位置为z=3

    setEnvironment(setEnvironmentDialog::BIOCHEMICALLAB);   //初始化环境
}

cdlOpenGLWidget::~cdlOpenGLWidget()
{
    if(isValid()){return;}  //程序对象初始化发生错误（如initializeGL(),resizeGL(),paintGL()）

    makeCurrent();  //调出当前状态
    glDeleteBuffers(1, &VBO_TRIANGLE);
    glDeleteBuffers(1, &VBO_RECTANGLE_1);
    glDeleteBuffers(1, &VBO_RECTANGLE_2);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO_ThreeD_1);
    glDeleteVertexArrays(4, VAOs);
    glDeleteVertexArrays(1, &lightVAO);
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

//加载模型
void cdlOpenGLWidget::loadModel(string path)
{
    if(myModel !=NULL)
        delete myModel;     //把现有的模型清空
    myModel=NULL;

    makeCurrent();
    //(当前OpenGL的状态,  模型文件路径)
    myModel = new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                        , path.c_str());
    Camera.Position=cameraPosInit(myModel->m_maxY,myModel->m_minY);     //根据模型Y坐标极值，设置不同模型的相机初始位置
    doneCurrent();
}

//选择环境
void cdlOpenGLWidget::setEnvironment(setEnvironmentDialog::EnvironmentType environment)
{
    myEnvironment = environment;
    switch (environment) {
    case setEnvironmentDialog::DESERT:
        clearColor=QVector3D(0.75f, 0.52f, 0.3f);
        dirlight_ambient=QVector3D(0.3f, 0.24f, 0.14f);
        dirlight_diffuse=QVector3D(0.7f, 0.42f, 0.26f);
        dirlight_specular=QVector3D(0.5f, 0.5f, 0.5f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsDesert[i];
        break;
    case setEnvironmentDialog::FACTTORY:
        clearColor=QVector3D(0.0f, 0.0f, 0.0f);
        dirlight_ambient=QVector3D(0.05f, 0.05f, 0.1f);
        dirlight_diffuse=QVector3D(0.2f, 0.2f, 0.7);
        dirlight_specular=QVector3D(0.7f, 0.7f, 0.7f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsFactory[i];
        break;
    case setEnvironmentDialog::HORROR:
        clearColor=QVector3D(0.0f, 0.0f, 0.0f);
        dirlight_ambient=QVector3D(0.0f, 0.0f, 0.0f);
        dirlight_diffuse=QVector3D(0.05f, 0.05f, 0.05);
        dirlight_specular=QVector3D(0.2f, 0.2f, 0.2f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsHorror[i];
        break;
    case setEnvironmentDialog::BIOCHEMICALLAB:
        clearColor=QVector3D(0.9f, 0.9f, 0.9f);
        dirlight_ambient=QVector3D(0.5f, 0.5f, 0.5f);
        dirlight_diffuse=QVector3D(1.0f, 1.0f, 1.0f);
        dirlight_specular=QVector3D(1.0f, 1.0f, 1.0f);
        for(int i=0;i<4;i++) pointLightColors[i]=pointLightColorsBiochemicalLab[i];
        break;
    default:
        break;
    }

}

setEnvironmentDialog::EnvironmentType cdlOpenGLWidget::getMyEnvironment() const
{
    return myEnvironment;
}

void cdlOpenGLWidget::setMyEnvironment(const setEnvironmentDialog::EnvironmentType &value)
{
    myEnvironment = value;
}


//----------------------------------------------------主程序------------------------------------------------------------------
float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };   //纹理效果背景颜色
float Ratio = 0.5;

void cdlOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //--------------------------------------------------------------------------------------------------
    //############################################着色器 ShaderProgram_withoutTexture####################
    //--------------------------------------------------------------------------------------------------
    bool success_withoutTexture;   //是否成功
    ShaderProgram_withoutTexture.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader_withoutTexture.vert");
    ShaderProgram_withoutTexture.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader_withoutTexture.frag");
    success_withoutTexture = ShaderProgram_withoutTexture.link();
    if(!success_withoutTexture){
        qDebug()<<"ERR:"<<ShaderProgram_withoutTexture.log();
    }
    //--------------------------------------------------------------------------------------------------
    //############################################着色器 ShaderProgram_withTexture#######################
    //--------------------------------------------------------------------------------------------------
    bool success_withTexture;   //是否成功
    ShaderProgram_withTexture.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader_withTexture.vert");
    ShaderProgram_withTexture.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader_withTexture.frag");
    success_withTexture = ShaderProgram_withTexture.link();
    if(!success_withTexture){
        qDebug()<<"ERR:"<<ShaderProgram_withTexture.log();
    }

    //纹理图案
    ShaderProgram_withTexture.bind();
    ShaderProgram_withTexture.setUniformValue("Wall", 0);      //通道0
    ShaderProgram_withTexture.setUniformValue("Container", 1);      //通道0
    ShaderProgram_withTexture.setUniformValue("ratio", Ratio);       //ratio初始值
    //--------------------------------------------------------------------------------------------------
    //############################################着色器 ShaderProgram_ThreeD############################
    //--------------------------------------------------------------------------------------------------
    bool success_ThreeD;   //是否成功
    ShaderProgram_ThreeD.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader_ThreeD.vert");
    ShaderProgram_ThreeD.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader_ThreeD.frag");
    success_ThreeD = ShaderProgram_ThreeD.link();
    if(!success_ThreeD){
        qDebug()<<"ERR:"<<ShaderProgram_ThreeD.log();
    }
    //--------------------------------------------------------------------------------------------------
    //############################################着色器 ShaderProgram_ThreeD_multiLight#################
    //--------------------------------------------------------------------------------------------------
    bool success_ThreeD_multiLight;   //是否成功
    ShaderProgram_ThreeD_multiLight.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader_ThreeD_multiLight.vert");
    ShaderProgram_ThreeD_multiLight.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader_ThreeD_multiLight.frag");
    success_ThreeD_multiLight = ShaderProgram_ThreeD_multiLight.link();
    if(!success_ThreeD_multiLight){
        qDebug()<<"ERR:"<<ShaderProgram_ThreeD_multiLight.log();
    }
    //--------------------------------------------------------------------------------------------------
    //############################################着色器 ShaderProgram_light#############################
    //--------------------------------------------------------------------------------------------------
    bool success_light;   //是否成功
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader_light.vert");
    ShaderProgram_light.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader_light.frag");
    success_light = ShaderProgram_light.link();
    if(!success_light){
        qDebug()<<"ERR:"<<ShaderProgram_light.log();
    }
    //--------------------------------------------------------------------------------------------------
    //############################################模型库#################################################
    //--------------------------------------------------------------------------------------------------
    myModel = new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                        , "D:/Study/file/demo/OpenGL/summarize/backpack/backpack.obj");
    //--------------------------------------------------------------------------------------------------
    //############################################纹理库#################################################
    //--------------------------------------------------------------------------------------------------
    //背景为透明image.png不自动填充背景色
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //纹理库
    Wall = new QOpenGLTexture(QImage(":/images/images/wall.jpg").mirrored());
    Container = new QOpenGLTexture(QImage(":/images/images/container2.png").mirrored());
    PandaLisa = new QOpenGLTexture(QImage(":/images/images/PandaLisa.jpg").mirrored());
    diffuseTexture = new QOpenGLTexture(QImage(":/images/images/container2.png").mirrored());
    specularTexture = new QOpenGLTexture(QImage(":/images/images/container2_specular.png").mirrored());
    emissionTexture = new QOpenGLTexture(QImage(":/images/images/matrix.jpg").mirrored());

    //纹理效果
    /*
     * GL_TEXTURE_WRAP_S    x轴
     * GL_TEXTURE_WRAP_T    y轴
     *
     * GL_REPEAT            //图片重复填充
     * GL_MIRRORED_REPEAT   //图片镜像重复填充
     * GL_CLAMP_TO_EDGE     //图片拉长填充
     * GL_CLAMP_TO_BORDER   //颜色填充
    */

    //纹理过滤
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
    Wall -> bind(0);
    Wall -> generateMipMaps();     //多级渐远纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);        //纹理过滤(适用于缩小)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         //纹理过滤（适用于放大）
    Container -> bind(1);
    Container -> generateMipMaps();     //多级渐远纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);        //纹理过滤(适用于缩小)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         //纹理过滤（适用于放大）
    PandaLisa -> bind(3);
    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    glGenVertexArrays(4, VAOs);
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO_TRIANGLE);
    glGenBuffers(1, &VBO_RECTANGLE_1);
    glGenBuffers(1, &VBO_RECTANGLE_2);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO_ThreeD_1);
    //-------------------------------------VAOs[0]-----------------------------------
    glBindVertexArray(VAOs[0]);
    //########绑定VBO_TRIANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
    //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //color attribute_location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //-------------------------------------VAOs[1]-----------------------------------
    glBindVertexArray(VAOs[1]);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_ebo), vertices_rectriangle_ebo, GL_STATIC_DRAW);
    //position attribute_location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //(该属性位置(传入shader中的location), 该数据大小, 数据类型, 是否需要标准化, 总数据大小, 偏移量)
    glEnableVertexAttribArray(0);
    //color attribute_location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //#################EBO###################
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rectriangle), indices_rectriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //-------------------------------------VAOs[2]-----------------------------------
    glBindVertexArray(VAOs[2]);
    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectriangle_texture_ebo), vertices_rectriangle_texture_ebo, GL_STATIC_DRAW);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rectriangle), indices_rectriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //-------------------------------------mesh1-------------------------------------
    myMesh=processMess();
    //-------------------------------------------------------------------------------
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
    glClearColor(clearColor.x(), clearColor.y(), clearColor.z(), 1.0f);       //初始化Widget BackgroundColor
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;      //初始化变换矩阵
    unsigned int time = QTime::currentTime().msec();    //获取当前时间
    float time1 = Time.elapsed()/50.0;

    QMatrix4x4 model;   //3D变换矩阵    物体对象
    QMatrix4x4 view;    //3D观察矩阵    摄像机
    QMatrix4x4 projection;      //3D投影矩阵    画布投影

    switch (myShape) {
    case Triangle:
        //-------------------------------obj 三角形-------------------------
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[0]);
        //-----------着色器------------
        ShaderProgram_withoutTexture.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);   //GL_ARRAY_BUFFER
        break;
    case Rect_1:
        //-------------------------------obj 矩形1-------------------------
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[1]);
        //-----------着色器------------
        ShaderProgram_withoutTexture.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //GL_ELEMENT_ARRAY_BUFFER
        break;
    case Rect_2:
        //-------------------------------obj 矩形2-------------------------
        //----------OpenGL对象---------
        glBindVertexArray(VAOs[2]);
        //-----------着色器------------
        ShaderProgram_withTexture.bind();
        //------------纹理效果----------
        Wall -> bind(0);
        Container -> bind(1);
        //##############Element1##############
        //------------矩阵变换----------
        matrix.translate(0.3, -0.3, 0);             //位移矩阵
        matrix.rotate(time, 0.0f, 0.0f, 1.0f);      //旋转矩阵
        ShaderProgram_withTexture.setUniformValue("Matrix", matrix);   //变换矩阵
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //GL_ELEMENT_ARRAY_BUFFER
        //##############Element2##############
        //------------矩阵变换----------
        matrix.setToIdentity();             //初始化矩阵
        matrix.translate(-0.5, 0.5, 0);     //位移矩阵
        matrix.scale(fabs(sin(time)));      //缩放矩阵
        ShaderProgram_withTexture.setUniformValue("Matrix", matrix);   //变换矩阵
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        break;
    case ThreeD_1:
        //-------------------------------obj 物体-------------------------
        //-----------着色器------------
        ShaderProgram_ThreeD.bind();
        //------------3D矩阵-----------
        /*
         * view         摄像机
         * model        物体对象
         * projection   画布投影
        */
        //view
        view = Camera.GetViewMatrix();
    //    view.translate(0.0, 0.0, -5.0);     //摄像机位于z=3的位置
        ShaderProgram_ThreeD.setUniformValue("view", view);
        //projection
        projection.perspective(Camera.Zoom, (float)width()/(float)height(), 0.1, 100);
        ShaderProgram_ThreeD.setUniformValue("projection", projection);
        //model
        model.rotate(time1, 1.0f, 1.0f, 0.5f);   //自转，绕y轴旋转
        ShaderProgram_ThreeD.setUniformValue("model", model);
        //物体材质
        ShaderProgram_ThreeD.setUniformValue("material.shininess", 32.0f);
        //光线颜色
    //    lightColor.setX(sin(time1 / 100 * 2.0f));       //改变光线颜色
    //    lightColor.setY(sin(time1 / 100 * 0.7f));
    //    lightColor.setZ(sin(time1 / 100 * 1.3f));
    //    QVector3D diffuseColor = lightColor * QVector3D(0.5, 0.5, 0.5);
    //    QVector3D ambientColor = diffuseColor * QVector3D(0.2, 0.2, 0.2);
    //    ShaderProgram.setUniformValue("light.ambient", ambientColor);
    //    ShaderProgram.setUniformValue("light.diffuse", diffuseColor);
    //    ShaderProgram.setUniformValue("light.specular", QVector3D(1.0, 1.0, 1.0));
        ShaderProgram_ThreeD.setUniformValue("light.position", Camera.Position);
        ShaderProgram_ThreeD.setUniformValue("light.direction", Camera.Front);
        ShaderProgram_ThreeD.setUniformValue("light.cutOff", (float)cos(12.5f*PI/180) );
        ShaderProgram_ThreeD.setUniformValue("light.outerCutOff", (float)cos(17.5f*PI/180) );
        ShaderProgram_ThreeD.setUniformValue("light.ambient", 0.4f, 0.4f, 0.4f);
        ShaderProgram_ThreeD.setUniformValue("light.diffuse", 0.9f, 0.9f, 0.9f);
        ShaderProgram_ThreeD.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        ShaderProgram_ThreeD.setUniformValue("light.constant", 1.0f);
        ShaderProgram_ThreeD.setUniformValue("light.linear", 0.09f);
        ShaderProgram_ThreeD.setUniformValue("light.quadratic", 0.032f);
        //光源位置
    //    lightPos.setX(cos(time1/100)*2.5);      //光源公转(物体受光照变化时需要用到光源的位置信息，因此在此传入)
    //    lightPos.setZ(sin(time1/100)*2.5);
        ShaderProgram_ThreeD.setUniformValue("viewPos", Camera.Position);

        for(unsigned int i = 0; i < 10; i++) {
            QMatrix4x4 model;
            model.translate(cubePosition[i]);
            float angle = 20.0f * i;
            model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
            model.rotate(time1, 1.0f, 1.0f, 0.5f);   //自转，绕y轴旋转
            ShaderProgram_ThreeD.setUniformValue("model", model);
            myMesh->Draw_once(ShaderProgram_ThreeD);
        }

        //-------------------------------obj 光源-------------------------
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

        myMesh->Draw_once(ShaderProgram_light);
        break;
    case ThreeD_2:
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

        for(unsigned int i = 0; i < 10; i++) {
            QMatrix4x4 model;
            model.translate(cubePosition[i]);
            float angle = 20.0f * i;
            model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
            model.rotate(time1, 1.0f, 1.0f, 0.5f);   //自转，绕y轴旋转
            ShaderProgram_ThreeD_multiLight.setUniformValue("model", model);
            myMesh->Draw_once(ShaderProgram_ThreeD_multiLight);
        }

        //-------------------------------obj 光源-------------------------
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

        for (int i=0;i<4;i++) {
            //model
            model.setToIdentity();
            model.translate(pointLightPositions[i]);      //移动位置
            //rotate(旋转角度, x轴, y轴, z轴)
            model.rotate(1.0, 1.0f, 5.0f, 0.5f);   //自传，绕y轴旋转
            model.scale(0.2);
            ShaderProgram_light.setUniformValue("model", model);
            //光源颜色
            ShaderProgram_light.setUniformValue("lightColor", pointLightColors[i]);

            myMesh->Draw_once(ShaderProgram_light);
        }
        break;
    case Model_1:
        if(myModel==NULL) return;
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
//        model.rotate(time1, 1.0f, 1.0f, 0.5f);
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

//----------------------------------------------------------other------------------------------------------------------------
Mesh_once* cdlOpenGLWidget::processMess()    //传入顶点和纹理数据
{
    //----------------顶点----------------
//    //1.顶点数据确定为36组
//    vector<Vertex> _vertices(36);
//    vector<unsigned int> _indices;
//    memcpy(&_vertices[0],vertices_ThreeD_1,sizeof(vertices_ThreeD_1));
//    for(int i=0;i<36;i++){
//        _indices.push_back(i);
//    }
    //1.顶点数据不确定
    vector<Vertex_once> _vertices;
    vector<unsigned int> _indices;

    for(int i=0;i<36;i++){
         Vertex_once vert;
         vert.Position[0]=vertices_ThreeD_1[i*8+0];
         vert.Position[1]=vertices_ThreeD_1[i*8+1];
         vert.Position[2]=vertices_ThreeD_1[i*8+2];
         vert.Normal[0]=vertices_ThreeD_1[i*8+3];
         vert.Normal[1]=vertices_ThreeD_1[i*8+4];
         vert.Normal[2]=vertices_ThreeD_1[i*8+5];
         vert.TexCoords[0]=vertices_ThreeD_1[i*8+6];
         vert.TexCoords[1]=vertices_ThreeD_1[i*8+7];
         _vertices.push_back(vert);
        _indices.push_back(i);
    }
    //----------------纹理----------------
    vector<Texture_once> _textures;
    Texture_once tex;

    //diffuseTexture
    tex.id=diffuseTexture->textureId();
    tex.type="diffuse";
    _textures.push_back(tex);
    //specularTexture
    tex.id=specularTexture->textureId();
    tex.type="specular";
    _textures.push_back(tex);
    //emissionTexture
    tex.id=emissionTexture->textureId();
    tex.type="emission";
    _textures.push_back(tex);


    return new Mesh_once(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
        ,_vertices,_indices,_textures);

}

QVector3D cdlOpenGLWidget::cameraPosInit(float maxY, float minY)
{
    QVector3D temp={0,0,0};
    float height=maxY-minY;     //模型高度
    temp.setZ(1.5*height);      //摄像机Z坐标 = 1.5倍高度
    if(minY>=0)
        temp.setY(height/2.0);  //摄像机Z坐标 = 0.5倍高度
    viewInitPos=temp;           //重置初始光源位置
    return temp;
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
    case Qt::Key_Up:
        Ratio+=0.1;
        break;
    case Qt::Key_Down:
        Ratio-=0.1;
        break;
    default:
        break;
    }

    if(Ratio > 1){
        Ratio = 1;
    }
    if(Ratio < 0){
        Ratio = 0;
    }
    ShaderProgram_withTexture.bind();
    ShaderProgram_withTexture.setUniformValue("ratio", Ratio);
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

