#version 410

layout(location = 0) in vec2 in_position;

void main()
{
    vec2 position = in_position;
    position.x += 0.4;
    position.y += 0.4;
    // ...
    // Modifiez `position` comme vous voulez
    // ...
    gl_Position = vec4(position, 0., 1.); // Ici on utilise maintenant `position` et non plus `in_position`
}