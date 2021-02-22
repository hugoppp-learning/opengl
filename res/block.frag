#version 330 core
out vec4 FragColor;
in vec3 f_pos;

void main()
{
    FragColor = vec4(f_pos,1.0f);//vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
