//Vertex.glsl 

#version 410

uniform mat4 view_projection_matrix;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 frag_uv;

void main() {
    gl_Position = view_projection_matrix * vec4(in_position, 1.0);
    frag_uv = in_uv;
}
