#version 410

in vec2 frag_uv;
uniform sampler2D screen_texture;
out vec4 out_color;

void main() {
    vec4 color = texture(screen_texture, frag_uv);
    out_color = vec4(color.rgb, 1.0);
}
