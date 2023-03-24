
#version 330 core   //顶上需要空一行，原因未知
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {       //物体材质
    sampler2D diffuse1;  //漫反射(光源和射入光线相同 -> 环境光和漫反射相同)   !!!纹理图必须在片段着色器里获取
    sampler2D specular1; //镜面反射
    float shininess;
};
uniform Material material;

struct SpotLight{       //点光源
    vec3 position; //手电筒位置
    vec3 direction; //手电筒聚光方向
    float cutOff;   //内圈聚光角度
    float outerCutOff;   //外圈聚光角度
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotlight;

struct DirLight{       //平行光源
    vec3 direction; //平行光方向
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirlight;

struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointlights[NR_POINT_LIGHTS];

uniform vec3 viewPos;   //观察方向

vec3 diffuseTexColor = vec3(texture(material.diffuse1, TexCoords));      //纹理图案
vec3 specularTexColor = vec3(texture(material.specular1, TexCoords));
//    vec3 specularTexColor = vec3(1) - vec3(texture(material.specular, TexCoords));  //让材质反光位置相反

//创建点光源（聚光）函数声明
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir);
//创建平行光源函数声明
vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir);
//创建点光源函数声明
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir);

void main(){

    vec3 norm = normalize(Normal);  //法线
    vec3 viewDir = normalize(viewPos - FragPos);    //观察方向

    vec3 result = vec3(0);
    result += CalcSpotLight(spotlight, norm, viewDir);
    result += CalcDirLight(dirlight, norm, viewDir);
    for(int i=0;i<NR_POINT_LIGHTS;i++)
         result += CalcPointLight(pointlights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);

}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);      //点光源光源射入方向
//    vec3 lightDir = normalize(-light.direction);  //平行光光源射入方向

    //ambient环境光
    vec3 ambient = diffuseTexColor * light.ambient;     // 环境光
    //diffuse入射光
    float diff = max(dot(norm, lightDir), 0.0);     //光源方向和法线夹角
    vec3 diffuse = diff * diffuseTexColor * light.diffuse;       //漫反射光
    //specular反射光
    vec3 reflectDir = reflect(-lightDir, norm);     //光源反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   //观察方向和反射光线夹角
    vec3 specular = spec * specularTexColor * light.specular;      //镜面发射光

    //聚光距离衰减(距离越远越暗，距离越近越亮)
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //    ambient *= attenuation;     //入射光衰减
    diffuse *= attenuation;     //漫反射衰减
    specular *= attenuation;    //镜面反射衰减

    //聚光平滑衰减
    float theta = dot(lightDir, normalize(-light.direction));   //聚光角度
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    //    ambient *= intensity;     //入射光衰减
    diffuse *= intensity;     //漫反射衰减
    specular *= intensity;    //镜面反射衰减

    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);  //平行光光源射入方向

    //ambient环境光
    vec3 ambient = diffuseTexColor * light.ambient;     // 环境光
    //diffuse入射光
    float diff = max(dot(norm, lightDir), 0.0);     //光源方向和法线夹角
    vec3 diffuse = diff * diffuseTexColor * light.diffuse;       //漫反射光
    //specular反射光
    vec3 reflectDir = reflect(-lightDir, norm);     //光源反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   //观察方向和反射光线夹角
    vec3 specular = spec * specularTexColor * light.specular;      //镜面发射光

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);      //点光源光源射入方向
    //ambient环境光
    vec3 ambient = diffuseTexColor * light.ambient;     // 环境光
    //diffuse入射光
    float diff = max(dot(norm, lightDir), 0.0);     //光源方向和法线夹角
    vec3 diffuse = diff * diffuseTexColor * light.diffuse;       //漫反射光
    //specular反射光
    vec3 reflectDir = reflect(-lightDir, norm);     //光源反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   //观察方向和反射光线夹角
    vec3 specular = spec * specularTexColor * light.specular;      //镜面发射光

    //聚光距离衰减(距离越远越暗，距离越近越亮)
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //    ambient *= attenuation;     //入射光衰减
    diffuse *= attenuation;     //漫反射衰减
    specular *= attenuation;    //镜面反射衰减

    return (ambient + diffuse + specular);
}

