//fragment.glsl

#version 410

in vec2 frag_uv;
uniform sampler2D my_texture;
out vec4 out_color;

void main() {
    out_color = texture(my_texture, frag_uv);
}
