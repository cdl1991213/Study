
#version 330 core   //真的搞不懂
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexPos;

uniform sampler2D textureBlue;
uniform sampler2D textureGold;

void main(){
//    FragColor = vec4(ourColor, 1.0f);
//    FragColor = texture(textureGold, ourTexPos)*vec4(1.0, 1.0, 0.0, 0.2);
    FragColor = texture(textureGold, ourTexPos);
}
