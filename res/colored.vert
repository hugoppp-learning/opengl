#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 v_norm;
out vec3 v_fragPos;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;

void main()
{
//    v_norm = mat3(transpose(inverse(u_m))) * v_norm;
    v_norm = mat3(transpose(inverse(u_m))) * aNorm;
    v_fragPos = vec3(u_m * vec4(aPos, 0));
    mat4 mvp = u_p * u_v * u_m;
    gl_Position = mvp * vec4(aPos, 1.0f);
}
