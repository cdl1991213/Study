
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    Normal = mat3(transpose(inverse(model))) * aNormal;   //基本模型坐标 --> 世界坐标
    FragPos = vec3(model * vec4(aPos, 1.0));     //基本模型坐标 --> 世界坐标
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
