#version 410

in vec2 frag_uv;
uniform sampler2D screen_texture;
out vec4 out_color;

void main() {
    vec4 color = texture(screen_texture, frag_uv);
    
    // Exemple : Appliquer un effet (Noir & Blanc)
    float grayscale = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    out_color = vec4(vec3(grayscale), 1.0);
}
