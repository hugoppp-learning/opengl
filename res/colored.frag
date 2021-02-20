#version 330 core
out vec4 FragColor;

in vec3 v_norm;
in vec3 v_fragPos;

uniform vec3 u_lightPos;
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
};
uniform LightMaterial u_light;

void main()
{
    vec3 norm = normalize(v_norm);

    // DIFFUSE
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diffuseStregth = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = u_material.diffuse* (u_light.diffuse * diffuseStregth);


    // SPECULAR
    vec3 viewDir = normalize(u_cameraPos - v_fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specularStrength = pow(max(dot(halfwayDir, norm), 0.0), u_material.shininess);
    vec3 specular =   u_light.specular * (u_material.specular * specularStrength);

    //AMBIENT
    vec3 ambient = u_material.ambient * u_light.ambient;

    vec3 light = diffuse + specular + ambient;

    FragColor = vec4(light, 1.0f);
}
