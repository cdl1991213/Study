
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {       //物体材质
    sampler2D diffuse;  //漫反射(光源和射入光线相同 -> 环境光和漫反射相同)   !!!纹理图必须在片段着色器里获取
    sampler2D specular;
    sampler2D emission;
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

uniform vec3 lightPos;  //光源位置
uniform vec3 viewPos;   //观察方向

void main(){
    vec3 diffuseTexColor = vec3(texture(material.diffuse, TexCoords));
    vec3 specularTexColor = vec3(texture(material.specular, TexCoords));
//    vec3 specularTexColor = vec3(1) - vec3(texture(material.specular, TexCoords));  //让反光位置相反
    //ambient环境光
    vec3 ambient = diffuseTexColor * light.ambient;     // 环境光
    //diffuse入射光
    vec3 norm = normalize(Normal);  //法线
    vec3 lightDir = normalize(lightPos - FragPos);  //光源射入方向
    float diff = max(dot(norm, lightDir), 0.0);     //光源方向和法线夹角
    vec3 diffuse = diff * diffuseTexColor * light.diffuse;       //漫反射光
    //specular反射光
    vec3 viewDir = normalize(viewPos - FragPos);    //观察方向
    vec3 reflectDir = reflect(-lightDir, norm);     //光源反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);   //观察方向和反射光线夹角
    vec3 specular = spec * specularTexColor * light.specular;      //镜面发射光
    //emission自发光
    vec3 emission = texture(material.emission, TexCoords).rgb;  //自发光

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);

}
