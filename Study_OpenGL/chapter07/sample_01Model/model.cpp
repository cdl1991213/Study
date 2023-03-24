#include "model.h"

//将obj格式的数据投入assimp中，转化为aiMesh格式的数据（obj --> aiMesh）
void Model::loadModel(string path)
{
    Assimp::Importer import;    //声明import
    //(path模型地址, 强制进行三角形处理 | 坐标轴颠倒)
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {  //判断是否加载成功
        qDebug() << "ERROR::ASSIMP::" << import.GetErrorString();
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));     //获取模型的目录
    processNode(scene->mRootNode, scene);       //遍历结点
}

//递归遍历获取aiMesh中所有Mesh的结点
void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];    //获取aiMesh数据
        meshes.push_back(processMesh(mesh, scene));         //目标Mesh的数据投入myMesh中
    }
    // then do the same for each of its children 递归遍历结点
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

//获取aiMesh中所有Mesh的数据，通过Mesh类的构造函数参数投入myMesh中（aiMesh --> myMesh）
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    //##################扫描顶点数据##################
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        if(m_maxX<mesh->mVertices[i].x) m_maxX=mesh->mVertices[i].x;
        if(m_maxY<mesh->mVertices[i].y) m_maxY=mesh->mVertices[i].y;
        if(m_minX>mesh->mVertices[i].x) m_minX=mesh->mVertices[i].x;
        if(m_minY>mesh->mVertices[i].y) m_minY=mesh->mVertices[i].y;
        Vertex vertex;
        //处理顶点位置、法线和纹理坐标
        //顶点
        QVector3D vector;
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex.Position = vector;
        //法线
        vector.setX(mesh->mNormals[i].x);
        vector.setY(mesh->mNormals[i].y);
        vector.setZ(mesh->mNormals[i].z);
        vertex.Normal = vector;
        //纹理坐标
        if(mesh->mTextureCoords[0]) // 判断是否有纹理坐标？
        {
            QVector2D vec;
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex.TexCoords = vec;
        } else
            vertex.TexCoords = QVector2D(0.0f, 0.0f);   //给予默认纹理坐标值

        //保存处理后的顶点位置、法线和纹理坐标
        vertices.push_back(vertex);
    }
    //##################处理索引##################
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];      //有多少个face
        for(unsigned int j = 0; j < face.mNumIndices; j++)  //每个face有多少个索引
            //保存处理后的索引数据
            indices.push_back(face.mIndices[j]);
    }

    //##################处理材质##################
    if(mesh->mMaterialIndex >= 0) {     //大于0表示AiMesh中存在纹理数据
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];     //读取纹理信息
        //diffuseMaps
        vector<Texture> diffuseMaps =
                loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        //specularMaps
        vector<Texture> specularMaps =
                loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(m_glFuns,vertices, indices, textures);

}

//加载纹理
vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
//    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//        bool skip = false;
//        for(unsigned int j = 0; j < textures_loaded.size(); j++) {
//            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
//                textures.push_back(textures_loaded[j]);
//                skip = true;
//                break;
//            }
//        }
//        if(!skip){
//            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(), directory);
//            texture.type = typeName;
//            texture.path = str.C_Str();
//            textures.push_back(texture);
//            textures_loaded.push_back(texture);
//        }
//    }
    return textures;
}

//unsigned int Model::TextureFromFile(const char *path, const string &directory)
//{
//    string filename = string(path);
//    filename = directory + '/' + filename;

//    QOpenGLTexture * texture=new QOpenGLTexture(QImage(filename.c_str()).mirrored());
//    if(texture==NULL) qDebug()<<"texture is NULL";
//    else qDebug()<<filename.c_str()<<"loaded";

//    return texture->textureId();
//}
