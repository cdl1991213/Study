
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;


in vec3 result;



void main(){

    FragColor = vec4(result, 1.0);



}
