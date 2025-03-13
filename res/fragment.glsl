//fragment.glsl

#version 410

in vec2 frag_uv;
in vec3 frag_normal;
in vec3 frag_position;

uniform vec3 light_position;
uniform vec3 light_direction;
uniform vec3 light_color;
uniform vec3 point_light_color;
uniform sampler2D my_texture;

out vec4 out_color;

void main() {
    vec3 normal = normalize(frag_normal);

    float diffuse_dir = max(dot(normal, -normalize(light_direction)), 0.0);
    vec3 dir_light = diffuse_dir * light_color;

    vec3 light_vector = light_position - frag_position;
    float distance = length(light_vector);
    vec3 light_dir = normalize(light_vector);

    float diffuse_point = max(dot(normal, light_dir), 0.0);
    float attenuation = 1.0 / (distance * distance);
    
    float light_intensity = 2.0;
    float point_light = diffuse_point * attenuation * light_intensity;
    vec3 point_light_effect = point_light * point_light_color;

    float ambient = 0.3;
    vec3 ambient_light = ambient * vec3(1.0, 1.0, 1.0);

    vec3 lighting = dir_light + point_light_effect + ambient_light;

    vec3 texture_color = texture(my_texture, frag_uv).rgb;
    vec3 shaded_color = texture_color * lighting;

    out_color = vec4(shaded_color, 1.0);
}
