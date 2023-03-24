#include "cdlopenglwidget.h"

unsigned int VBO_TRIANGLE,VBO_RECTANGLE,EBO,VAO,VBOColor;
unsigned int shaderProgram;
//顶点坐标
float vertices_triangle[] = {
    -0.5f, -0.5f, 0.0f,     //第一个顶点的x,y,z坐标
    0.5f, -0.5f, 0.0f,      //第二个顶点的x,y,z坐标
    0.0f, 0.5f, 0.0f        //第三个顶点的x,y,z坐标
};

float vertices_rectangle_vbo[] = {  //不借助EBO
    //第一个三角形
    0.5f, 0.5f, 0.0f,   //右上
    0.5f, -0.5f, 0.0f,  //右下
    -0.5f, 0.5f, 0.0f,  //左上
    //第二个三角形
    0.5f, -0.5f, 0.0f,  //右下
    -0.5f, -0.5f, 0.0f, //左下
    -0.5f, 0.5f, 0.0f,  //左上
};

float vertices_rectangle_ebo[] = {  //借助EBO
    0.5f, 0.5f, 0.0f,   //右上
    0.5f, -0.5f, 0.0f,  //右下
    -0.5f, -0.5f, 0.0f, //左下
    -0.5f, 0.5f, 0.0f,  //左上
};
//ebo索引，记录不重复顶点
unsigned int indices[] = {
    //第一个三角形
    0, 1, 3,
    //第二个三角形
    1, 2, 3
};

float verticesColor[] = {
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


//顶点着色器
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n" "void main()\n"
                                 "{\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

//片段着色器
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n""}\n\0";




cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void cdlOpenGLWidget::initializeGL()
{
    //初始化
    initializeOpenGLFunctions();

    //--------------------------------------------------------------------------------------------------
    //############################################OpenGL对象#############################################
    //--------------------------------------------------------------------------------------------------
    //1.创建对象
    //创建VAO，并绑定到缓存
    //参数(需要创建的缓存数量，ID)
    glGenVertexArrays(1, &VAO);
    //创建VBO
    //参数(需要创建的缓存数量，对象名称)
//    glGenBuffers(1, &VBO_TRIANGLE);
    glGenBuffers(1, &VBO_RECTANGLE);
    glGenBuffers(1, &EBO);
//    glGenBuffers(1, &VBOColor);


    //2.绑定对象
    //绑定VAO
    //所有跟GL_ARRAY_BUFFER有关的操作都会被记录
    glBindVertexArray(VAO);

//    //########绑定VBO_TRIANGLE#########
//    //管理内存中的数据，并将数据传到缓存
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
//    //创建vertices大小的数据存储
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
//    //解析属性（数据的大小、位置）,每3个作为一个属性位置
//    //(解析后的属性值存储的位置信息【开启属性时用到】，当前位置存储几个数据，GL_FLOAT, GL_FALSE, 一个顶点信息的步长，偏移量)
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//    //########绑定VBO_RECTANGLE#########
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectangle_vbo), vertices_rectangle_vbo, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    //用线条填充Polygon
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //########借助EBO绑定VBO_RECTANGLE#########
    glBindBuffer(GL_ARRAY_BUFFER, VBO_RECTANGLE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectangle_ebo), vertices_rectangle_ebo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //用线条填充Polygon
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //EBO部分
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//    //########绑定VBOColor#########
//    glBindBuffer(GL_ARRAY_BUFFER, VBOColor);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor), verticesColor, GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    //3.启用属性
    //开启VAO中的第一个属性
    glEnableVertexAttribArray(0);

    //4.绑定空缓冲区，达到释放对象的效果
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //--------------------------------------------------------------------------------------------------
    //############################################着色器##################################################
    //--------------------------------------------------------------------------------------------------
    //###########顶点着色器###############
    //1.创建顶点着色器对象
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //2.绑定源码到顶点着色器对象
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //3.编译顶点着色器源码
    glCompileShader(vertexShader);
//    //4.检查是否error
//    int success;char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog;
//    }
    //###########片段着色器###############
    //1.创建片段着色器对象
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //2.绑定源码到片段着色器对象
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //3.编译片段着色器源码
    glCompileShader(fragmentShader);
//    //4.检查是否error
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog;
//    }
    //###########链接###############
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
//    //检查是否error
//    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog;
//    }
    //删除顶点着色器对象、片段着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //--------------------------------------------------------------------------------------------------


}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    //暂时先不用的参数
    Q_UNUSED(w);Q_UNUSED(h);
}

void cdlOpenGLWidget::paintGL()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置widget背景颜色
    glClear(GL_COLOR_BUFFER_BIT);//使用widget背景颜色

    //画图的时候使用shaderProgram
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    //画三角形
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    //画矩形VBO
//    glDrawArrays(GL_TRIANGLES, 0, 6);
    //借助EBO画矩形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //仅借助indices画矩形
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);
}
