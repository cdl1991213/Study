
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec2 TexPos;

uniform sampler2D PandaLisa;
uniform sampler2D Wood;

void main(){
    FragColor = texture(PandaLisa, TexPos);
//    FragColor = mix(texture(PandaLisa, TexPos),
//                    texture(rabbit, TexPos),0.5);
}
