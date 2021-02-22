#version 330 core
out vec4 FragColor;

in vec3 v_norm;
in vec3 v_fragPos;

uniform vec3 u_cameraPos;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material u_material;

struct LightMaterial {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;

    float linear;
    float quadratic;
};
uniform LightMaterial u_light;

void main()
{
    vec3 norm = normalize(v_norm);

    // DIFFUSE
    vec3 lightDir = normalize(u_light.position - v_fragPos);
    float diffuseStregth = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = u_material.diffuse* (u_light.diffuse * diffuseStregth);

    // SPECULAR
    vec3 viewDir = normalize(u_cameraPos - v_fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specularStrength = pow(max(dot(halfwayDir, norm), 0.0), u_material.shininess);
    vec3 specular =   u_light.specular * (u_material.specular * specularStrength);

    //AMBIENT
    vec3 ambient = u_material.ambient * u_light.ambient;
    float distance = length(u_light.position - v_fragPos);
    float attenuation = 1 / (1 + u_light.linear * distance + u_light.quadratic * distance * distance);

    vec3 light = attenuation * (diffuse + specular + ambient);

    FragColor = vec4(light, 1.0f);
}
