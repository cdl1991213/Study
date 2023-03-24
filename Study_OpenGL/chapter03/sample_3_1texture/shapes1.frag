
#version 330 core   //真的搞不懂
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexPos;

uniform sampler2D textureBlue;
uniform sampler2D textureGold;

void main(){
//    FragColor = vec4(ourColor, 1.0f);
    FragColor = mix(texture(textureBlue, ourTexPos), texture(textureGold, ourTexPos), 0.5);
//    FragColor = texture(textureBlue, ourTexPos);
}
