
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
