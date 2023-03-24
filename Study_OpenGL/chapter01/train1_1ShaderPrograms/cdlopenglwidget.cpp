#include "cdlopenglwidget.h"

unsigned int VBO,VAO;
unsigned int VBOs[2],VAOs[2];
unsigned int shaderProgram1, shaderProgram2;

//顶点坐标
//通过一个VBO和VAO创建三角形
float vertices_01_triangles[] = {
    -0.9f, -0.5f, 0.0f,     //第一个顶点的x,y,z坐标
    -0.0f, -0.5f, 0.0f,      //第二个顶点的x,y,z坐标
    -0.45f, 0.5f, 0.0f,        //第三个顶点的x,y,z坐标

    0.0f, -0.5f, 0.0f,     //第一个顶点的x,y,z坐标
    0.9f, -0.5f, 0.0f,      //第二个顶点的x,y,z坐标
    0.45f, 0.5f, 0.0f        //第三个顶点的x,y,z坐标
};

//通过不同VBO和VAO创建三角形
float vertices_02_first_triangle[] = {
    -0.9f, -0.5f, 0.0f,     //第一个顶点的x,y,z坐标
    -0.0f, -0.5f, 0.0f,      //第二个顶点的x,y,z坐标
    -0.45f, 0.5f, 0.0f,        //第三个顶点的x,y,z坐标
};
float vertices_02_second_triangle[] = {
    0.0f, -0.5f, 0.0f,     //第一个顶点的x,y,z坐标
    0.9f, -0.5f, 0.0f,      //第二个顶点的x,y,z坐标
    0.45f, 0.5f, 0.0f        //第三个顶点的x,y,z坐标
};

//顶点着色器
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n" "void main()\n"
                                 "{\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

//片段着色器1
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n""}\n\0";
//片段着色器2
const char *fragmentShader2Source = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   " FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n""}\n\0";


cdlOpenGLWidget::cdlOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void cdlOpenGLWidget::initializeGL()
{
    //初始化
    initializeOpenGLFunctions();

    //--------------------------------------------------------------------------------------------------
    //########################################通过一个VBO和VAO创建#########################################
    //--------------------------------------------------------------------------------------------------
    //一次创建单个对象
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_01_triangles), vertices_01_triangles, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //--------------------------------------------------------------------------------------------------
    //########################################通过不同VBO和VAO创建#########################################
    //--------------------------------------------------------------------------------------------------
    //一次创建多个对象
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    //第一个VBO和VAO
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_02_first_triangle), vertices_02_first_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);   //VAOs[0]的第一个属性

    //第二个VBO和VAO
    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_02_second_triangle), vertices_02_second_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);   //VAOs[1]的第一个属性

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
    //###########片段着色器1###############
    //1.创建片段着色器对象
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    //2.绑定源码到片段着色器对象
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource, NULL);
    //3.编译片段着色器源码
    glCompileShader(fragmentShader1);
//    //4.检查是否error
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog;
//    }
    //###########片段着色器2###############
    //1.创建片段着色器对象
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    //2.绑定源码到片段着色器对象
    glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
    //3.编译片段着色器源码
    glCompileShader(fragmentShader2);
//    //4.检查是否error
//    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog;
//    }
    //###########链接1###############
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
//    //检查是否error
//    glGetShaderiv(shaderProgram1, GL_LINK_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(shaderProgram1, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog;
//    }
    //###########链接2###############
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
//    //检查是否error
//    glGetShaderiv(shaderProgram2, GL_LINK_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(shaderProgram2, 512, NULL, infoLog);
//        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog;
//    }
    //删除顶点着色器对象、片段着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
    //--------------------------------------------------------------------------------------------------

}

void cdlOpenGLWidget::resizeGL(int w, int h)
{
    //暂时先不用的参数
    Q_UNUSED(w);Q_UNUSED(h);
}

void cdlOpenGLWidget::paintGL()
{
    glClearColor(0.5f, 0.1f, 0.4f, 1.0f);//设置widget背景颜色
    glClear(GL_COLOR_BUFFER_BIT);//使用widget背景颜色

//    //通过一个VBO和VAO创建
//    //画图的时候使用shaderProgram1
//    glUseProgram(shaderProgram1);
//    glBindVertexArray(VAO);
//    //画三角形
//    glDrawArrays(GL_TRIANGLES, 0, 6);


    //通过不同VBO和VAO创建
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);




}
