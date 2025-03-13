//Vertex.glsl 

#version 410

uniform mat4 view_projection_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec2 frag_uv;
out vec3 frag_normal;
out vec3 frag_position;

vec3 apply_matrix_to_position(mat4 matrix, vec3 point) {
    vec4 tmp = matrix * vec4(point, 1.0);
    return tmp.xyz / tmp.w;
}

vec3 apply_matrix_to_direction(mat4 matrix, vec3 direction) {
    vec4 tmp = matrix * vec4(direction, 0.0);
    return normalize(tmp.xyz);
}

void main() {
    frag_position = apply_matrix_to_position(model_matrix, in_position);
    frag_normal = apply_matrix_to_direction(normal_matrix, in_normal);
    frag_uv = in_uv;
    
    gl_Position = view_projection_matrix * vec4(frag_position, 1.0);
}
