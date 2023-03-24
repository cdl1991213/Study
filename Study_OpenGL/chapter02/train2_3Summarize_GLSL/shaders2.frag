
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec3 ourColor;

void main(){
    FragColor = vec4(ourColor, 1.0f);
}
