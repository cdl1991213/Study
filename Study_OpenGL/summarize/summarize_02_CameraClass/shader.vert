
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;

out vec2 TexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    TexPos = aTexPos;
//    TexPos = vec2(1 - aTexPos.s, aTexPos.t);   //纹理图左右翻转
}
