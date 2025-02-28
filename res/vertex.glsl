//Vertex.glsl

#version 410

uniform float aspect_ratio;
uniform float time;

layout(location = 0) in vec2 in_position;

void main()
{
    vec2 position = in_position;
    position.x /= aspect_ratio;

    position.x += sin(time); //l'objet reste en 0,0 mais son visuel bouge

    gl_Position = vec4(position, 0.0, 1.0);
}