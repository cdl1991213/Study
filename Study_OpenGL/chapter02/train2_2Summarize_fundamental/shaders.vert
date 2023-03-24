
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
