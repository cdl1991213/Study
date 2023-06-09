﻿#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QOpenGLTexture>

#include "mesh.h"       //绘制时的最小单元mesh

class Model {
public:
    Model(QOpenGLFunctions_3_3_Core *glfuns,const char *path) :m_glFuns(glfuns) {
        loadModel(path);
    }

    float m_maxX=-100.0;
    float m_maxY=-100.0;
    float m_minX=100.0;
    float m_minY=100.0;
    vector<Texture> textures_loaded;

    void Draw(QOpenGLShaderProgram &shader) {
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);

    }

private:
    // model data
    QOpenGLFunctions_3_3_Core *m_glFuns;
    vector<Mesh> meshes;
    string directory;
    void loadModel(string path);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
//    unsigned int TextureFromFile(const char *path, const string &directory);
};

#endif // MODEL_H
