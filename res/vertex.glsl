//Vertex.glsl 

#version 410

uniform mat4 view_projection_matrix;
layout(location = 0) in vec3 in_position;

out vec3 vertex_position; // Variable transmise au fragment shader

void main() {
    gl_Position = view_projection_matrix * vec4(in_position, 1.0);
    vertex_position = in_position; // Assigner la position du vertex pour le passer au fragment shader
}
