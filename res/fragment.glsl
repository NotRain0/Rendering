//fragment.glsl

#version 410

in vec2 frag_uv;
in vec3 frag_normal;
in vec3 frag_position;

uniform vec3 light_position;
uniform vec3 light_direction;
uniform sampler2D my_texture;

out vec4 out_color;

void main() {
    vec3 normal = normalize(frag_normal);

    float diffuse_dir = max(dot(normal, -normalize(light_direction)), 0.0);

    vec3 light_vector = light_position - frag_position; // Vecteur lumière → pixel
    float distance = length(light_vector);
    vec3 light_dir = normalize(light_vector);

    float diffuse_point = max(dot(normal, light_dir), 0.0);
    
    float attenuation = 1.0 / (distance * distance);
    
    float light_intensity = 2.0;
    float point_light = diffuse_point * attenuation * light_intensity;

    float ambient = 0.3;
    //float lighting = max(diffuse_dir, 0.0) + max(point_light, 0.0) + max(ambient, 0.0);
    float lighting = max(diffuse_dir, 0.0); //+ max(point_light, 0.0) + max(ambient, 0.0);
    //float lighting = max(point_light, 0.0);

    vec3 texture_color = texture(my_texture, frag_uv).rgb;
    vec3 shaded_color = texture_color * lighting;

    out_color = vec4(shaded_color, 1.0);
}
