//Vertex.glsl 

#version 410

uniform mat4 view_projection_matrix;
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec2 frag_uv;
out vec3 frag_normal;
out vec3 frag_position;

void main() {
    vec4 world_position = view_projection_matrix * vec4(in_position, 1.0);
    gl_Position = world_position;
    
    frag_uv = in_uv;
    frag_normal = normalize(in_normal);
    frag_position = in_position; 
}
