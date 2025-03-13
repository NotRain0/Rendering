//fragment.glsl

#version 410

in vec2 frag_uv;
in vec3 frag_normal;

uniform vec3 light_direction;
uniform sampler2D my_texture;

out vec4 out_color;

void main() {
    vec3 normal = normalize(frag_normal);
    float diffuse = max(dot(normal, -normalize(light_direction)), 0.0);

    float ambient = 0.3;
    float lighting = max(diffuse + ambient, 0.0);

    vec3 texture_color = texture(my_texture, frag_uv).rgb;
    vec3 shaded_color = texture_color * lighting;

    out_color = vec4(shaded_color, 1.0);
}
