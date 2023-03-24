#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <string>
#include <vector>
using namespace std;
struct Vertex_once {
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};
struct Texture_once {
    unsigned int id;
    string type;
    string path;
};

class Mesh_once {
public:
    // mesh data
    vector<Vertex_once> vertices;
    vector<unsigned int> indices;
    vector<Texture_once> textures;

    void Draw_once(QOpenGLShaderProgram &shader);
    Mesh_once(QOpenGLFunctions_3_3_Core *glFuns,
         vector<Vertex_once> vertices, vector<unsigned int> indices, vector<Texture_once> textures);
private:
    // render data
    unsigned int VAO, VBO, EBO;
    void setupMesh_once();
private: QOpenGLFunctions_3_3_Core *m_glFuns;
};
