
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;   //物体颜色
uniform vec3 lightColor;    //光源颜色
uniform vec3 lightPos;  //光源位置
uniform vec3 viewPos;   //观察方向

void main(){
//        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);   //红色
    //ambient
    float ambientSrength = 0.1;
    vec3 ambient = ambientSrength * lightColor;     // 环境光
    //diffuse
    vec3 norm = normalize(Normal);  //法线
    vec3 lightDir = normalize(lightPos - FragPos);  //光源射入方向
    float diff = max(dot(norm, lightDir), 0.0);     //光源方向和法线夹角
    vec3 diffuse = diff * lightColor;       //漫反射光
    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);    //观察方向
    vec3 reflectDir = reflect(-lightDir, norm);     //光源反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);   //观察方向和反射光线夹角
    vec3 specular =  specularStrength * spec * lightColor;      //镜面发射光

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);



}
