//Vertex.glsl 

#version 410

uniform mat4 view_projection_matrix;
layout(location = 0) in vec3 in_position; // Maintenant en 3D

void main() {
    gl_Position = view_projection_matrix * vec4(in_position, 1.0);
}
