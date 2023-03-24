
#version 330 core   //真的搞不懂
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexPos;

uniform sampler2D textureBlue;
uniform sampler2D textureGold;

void main(){
    FragColor = texture(textureGold, ourTexPos);
}
