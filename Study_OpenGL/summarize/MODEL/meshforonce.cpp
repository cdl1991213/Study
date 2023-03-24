#include "meshforonce.h"

Mesh_once::Mesh_once(QOpenGLFunctions_3_3_Core *glFuns,
           vector<Vertex_once> vertices, vector<unsigned int> indices, vector<Texture_once> textures)
    :m_glFuns(glFuns)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh_once();
}

void Mesh_once::setupMesh_once()  //读取顶点数据
{
    //创建VBO和VAO对象，并赋予ID
    m_glFuns->glGenVertexArrays(1, &VAO);
    m_glFuns->glGenBuffers(1, &VBO);
    m_glFuns->glGenBuffers(1,&EBO);
    //绑定VBO和VAO对象
    m_glFuns->glBindVertexArray(VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    m_glFuns->glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex_once),
                           &vertices[0], GL_STATIC_DRAW);
    m_glFuns->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    m_glFuns->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                           indices.size() * sizeof(unsigned int),&indices[0], GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    m_glFuns->glEnableVertexAttribArray(0);
    m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_once),
                                    (void*)offsetof(Vertex_once, Normal));

    m_glFuns->glEnableVertexAttribArray(1);
    m_glFuns->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_once),
                                    (void*)offsetof(Vertex_once, TexCoords));
    m_glFuns->glEnableVertexAttribArray(2);
}


void Mesh_once::Draw_once(QOpenGLShaderProgram &shader)   //读取纹理数据
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int emissionNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++) { //遍历纹理
        m_glFuns->glActiveTexture(GL_TEXTURE0 + i);     //纹理通道
        string number;
        string name = textures[i].type;

        if(name == "diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "specular")
            number = std::to_string(specularNr++);
        else if(name == "emission")
            number = std::to_string(emissionNr++);

        shader.setUniformValue(("material." + name + number).c_str(), i);   //纹理接口

        m_glFuns->glBindTexture(GL_TEXTURE_2D, textures[i].id); //绑定纹理通道和纹理接口

    }

    m_glFuns->glBindVertexArray(VAO);
    m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 36);
}
