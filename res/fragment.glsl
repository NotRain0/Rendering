//fragment.glsl

#version 410

in vec3 vertex_position; // Recevoir la position du vertex

out vec4 out_color;

void main() {
    // Utilise la position du vertex comme couleur
    // Normalise la position pour l'utiliser comme couleur (les positions peuvent être négatives)
    out_color = vec4((vertex_position + 1.0) / 2.0, 1.0);
}