
#version 330 core   //真的搞不懂
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexPos;

uniform sampler2D textureBlue;
uniform sampler2D textureGold;
uniform float ratio;

void main(){
    FragColor = mix(texture(textureBlue, ourTexPos),
                    texture(textureGold, ourTexPos),ratio);
//    FragColor = texture(textureBlue, ourTexPos);
}
