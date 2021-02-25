#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_norm;
out vec3 f_pos;
out vec3 f_norm;

uniform mat4 u_v;
uniform mat4 u_p;

void main() {
    mat4 vp = u_p * u_v;
    f_pos = vec3(float(v_pos.x), float(v_pos.y), float(v_pos.z));
    f_norm = vec3(v_norm);
    gl_Position = vp * vec4(f_pos,1);
}
