
#version 330 core   //真的搞不懂
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float xOffset;

out vec3 ourColor;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
//    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0f);  //水平偏移 + 垂直颠倒
    ourColor = aPos;
}
