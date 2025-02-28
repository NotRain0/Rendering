//fragment.glsl

#version 410

uniform float opacity; // Ajoute une variable uniform pour l'opacité
out vec4 out_color;

void main()
{
    out_color = vec4(0.0, 1.0, 1.0, opacity); // Utilise l'opacité fournie
}
