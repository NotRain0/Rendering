//Vertex.glsl 

#version 410

uniform mat4 view_projection_matrix;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec2 frag_uv;
out vec3 frag_normal;

void main() {
    gl_Position = view_projection_matrix * vec4(in_position, 1.0);
    frag_uv = in_uv;
    frag_normal = in_normal;
}