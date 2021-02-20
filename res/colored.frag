#version 330 core
out vec4 FragColor;

in vec3 v_norm;
in vec3 v_fragPos;

uniform vec3 u_lightPos;
uniform vec4 u_ambientColor;
uniform vec4 u_modelColor;
uniform vec4 u_defuseColor;
uniform vec3 u_cameraPos;
uniform float u_shininess;

void main()
{

    vec3 norm = normalize(v_norm);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diffuseStregth = max(dot(lightDir, norm), 0.0f);

    vec3 diffuseColor = vec3 (1.0f, 1.0f, 1.0f);
    vec3 diffuse = u_defuseColor.xyz * diffuseStregth;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_cameraPos - v_fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
//    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(halfwayDir, norm), 0.0), u_shininess);
    vec3 specular = specularStrength * spec * u_defuseColor.xyz;

    vec3 light = diffuse + u_ambientColor.xyz + specular;

    FragColor = vec4(light * u_modelColor.xyz, 1.0f);
}
