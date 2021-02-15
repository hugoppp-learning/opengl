#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec4 v_vertexColor;
out vec2 v_texCoord;

uniform mat4 u_mvp;
void main()
{
   v_vertexColor = vec4(aColor, 1.0f);
   gl_Position = u_mvp * vec4(aPos, 1.0f);
   v_texCoord = aTexCoord;
}
