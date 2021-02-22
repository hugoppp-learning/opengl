#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in int v_blockId;
out vec3 f_pos;

uniform mat4 u_v;
uniform mat4 u_p;

void main() {
    mat4 vp = u_p * u_v;
    f_pos = vec3(float(v_pos.x), float(v_pos.y), float(v_pos.z));
    gl_Position = vp * vec4(f_pos, 1.0f);
}
