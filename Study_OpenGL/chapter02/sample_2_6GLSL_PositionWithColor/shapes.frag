
#version 330 core   //真的搞不懂
out vec4 FragColor;

in vec3 ourColor;

void main(){
    FragColor = vec4(ourColor, 1.0f);
}
