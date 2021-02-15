#version 330 core
out vec4 FragColor;

in vec4 v_vertexColor;
in vec2 v_texCoord;

uniform sampler2D u_ourTexture;

void main()
{
    if (v_vertexColor == vec4(0, 0, 0, 1)){
        FragColor = texture(u_ourTexture, v_texCoord);
    }
    else {
        FragColor = texture(u_ourTexture, v_texCoord) * v_vertexColor;
    }
}
