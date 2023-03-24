
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec3 Color;
in vec2 TexPos;

uniform sampler2D Wall;
uniform sampler2D Container;
uniform float ratio;


void main(){
//    FragColor = texture(Wall, TexPos);        //单张图片作纹理
    FragColor = mix(texture(Wall, TexPos),      //两张图片以ratio比率融合
                    texture(Container, TexPos), ratio);
}
