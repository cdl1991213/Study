
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec3 Color;

void main(){
//    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);   //红色
    FragColor = vec4(Color, 1.0f);   //红色
}
