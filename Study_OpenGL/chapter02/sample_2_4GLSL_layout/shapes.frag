
#version 330 core   //不知道为什么要空一行才能正常着色...
out vec4 FragColor;

in vec4 vertexColor;

void main(){
//    FragColor = vec4(1.0f, 0.0f, 0.5f, 1.0f);
//    FragColor = vertexColor;
    FragColor = vec4(vertexColor.xyz, 1.0f);
}
