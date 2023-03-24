
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 Color;
out vec2 TexPos;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    Color = aColor;
    TexPos = aTexPos;
//    TexPos = vec2(1 - aTexPos.s, aTexPos.t);   //纹理图左右翻转
}
