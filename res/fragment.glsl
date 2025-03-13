//fragment.glsl

#version 410

in vec2 frag_uv;
in vec3 frag_normal;

out vec4 out_color;

void main() {
    vec3 normal_color = (frag_normal + vec3(1.0)) * 0.5;
    out_color = vec4(frag_normal, 1.0);
}