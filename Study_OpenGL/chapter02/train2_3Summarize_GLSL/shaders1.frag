
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

//in vec4 vertexColor;
uniform vec4 ourColor;

void main(){
//    FragColor = vec4(vertexColor.xyz, 1.0f);
    FragColor = ourColor;
}
