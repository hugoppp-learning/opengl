#version 330 core
out vec4 FragColor;
in vec3 f_pos;
in vec3 f_norm;

void main()
{
    vec3 lightDir = normalize(vec3(-0.1, -1, -0.6));
    float diffuseStrength = max(dot(normalize(f_norm), lightDir),0.0);
    FragColor = vec4(vec3(f_pos/64) * (diffuseStrength + 0.05), 1);//vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
