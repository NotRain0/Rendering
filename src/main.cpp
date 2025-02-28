#include "opengl-framework/opengl-framework.hpp"

int main()
{
    gl::init("TPs de Rendering"); 
    gl::maximize_window(); 

    glEnable(GL_BLEND); // Active le blending pour l'opacité
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Fonction de mélange standard

    auto const rectangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0}},
            .data   = {
                -0.5f, -0.5f, // Position2D du 1er sommet
                +0.5f, -0.5f, // Position2D du 2ème sommet
                +0.5f, +0.5f, // Position2D du 3ème sommet
                -0.5f, +0.5f  // Position2D du 4ème sommet
            },
        }},
        .index_buffer   = {
            0, 1, 2,
            0, 2, 3  
        },
    }};

    auto const shader = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment.glsl"},
    }};
    
    while (gl::window_is_open())
    {
        glClearColor(0.f, 0.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    
        shader.bind();
    
        float aspectRatio = gl::framebuffer_aspect_ratio();
        shader.set_uniform("aspect_ratio", aspectRatio);

        // Dessine plusieurs carrés avec différents décalages de temps et opacités
        for (int i = 0; i < 20; i++) {
            float timeOffset = 0.1f * i; // Décalage de temps pour le mouvement
            float opacity = 1.0f - (0.05f * i); // Réduit l'opacité pour chaque carré suivant

            float currentTime = gl::time_in_seconds() - timeOffset;
            shader.set_uniform("time", currentTime);
            shader.set_uniform("opacity", opacity);

            rectangle_mesh.draw(); // Dessine le carré avec les paramètres actuels
        }
    }
}
