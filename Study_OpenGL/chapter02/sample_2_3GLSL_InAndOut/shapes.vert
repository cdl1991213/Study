
#version 330 core   //不知道为什么要空一行才能正常着色...
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
