
#version 330 core   //顶上需要空一行，原因未知
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 result;

struct Material {       //物体材质
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light{       //光源
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;  //光源位置
uniform vec3 viewPos;   //观察方向

void main(){
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;   //基本模型坐标 --> 世界坐标
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));     //基本模型坐标 --> 世界坐标

    //position
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);

    //ambient
    vec3 ambient = light.ambient * material.ambient;     // 环境光
    //diffuse
    vec3 norm = normalize(Normal);  //法线
    vec3 lightDir = normalize(lightPos - FragPos);  //光源射入方向
    float diff = max(dot(norm, lightDir), 0.0);     //光源方向和法线夹角
    vec3 diffuse = diff * light.diffuse * material.diffuse;       //漫反射光
    //specular
    vec3 viewDir = normalize(viewPos - FragPos);    //观察方向
    vec3 reflectDir = reflect(-lightDir, norm);     //光源反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);   //观察方向和反射光线夹角
    vec3 specular = spec * light.specular * material.specular;      //镜面发射光

    result = (ambient + diffuse + specular);
}
