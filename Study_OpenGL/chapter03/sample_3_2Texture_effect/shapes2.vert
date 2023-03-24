
#version 330 core   //真的搞不懂
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 ourColor;
out vec2 ourTexPos;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    ourColor = aColor;
    ourTexPos = aTexPos;

}
