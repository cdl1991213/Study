﻿
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;     //顶点坐标
layout (location = 1) in vec3 aNormal;   //法线值
layout (location = 2) in vec2 aTexCoords;    //纹理坐标

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    TexCoords=aTexCoords;

    Normal = mat3(transpose(inverse(model))) * aNormal;   //基本模型坐标 --> 世界坐标
    FragPos = vec3(model * vec4(aPos, 1.0));     //基本模型坐标 --> 世界坐标

    //position
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);

}
