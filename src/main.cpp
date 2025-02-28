#include "opengl-framework/opengl-framework.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp> 

int main() {
    gl::init("3D Rendering");
    gl::maximize_window();

    auto camera = gl::Camera{};
    gl::set_events_callbacks({camera.events_callbacks()});

    // Création du cube avec des UVs
    auto const cube_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {
                gl::VertexAttribute::Position3D{0}, // Position 3D
                gl::VertexAttribute::UV{1}         // UV mapping
            },
            .data = {
                // Position          // UV
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // 0 - Face avant
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // 1
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // 2
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // 3

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // 4 - Face arrière
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // 5
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // 6
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f   // 7
            },
        }},
        .index_buffer = {
            0, 1, 2, 0, 2, 3, // Face avant
            4, 5, 6, 4, 6, 7, // Face arrière
            4, 0, 3, 4, 3, 7, // Face gauche
            1, 5, 6, 1, 6, 2, // Face droite
            3, 2, 6, 3, 6, 7, // Face haut
            4, 5, 1, 4, 1, 0  // Face bas
        },
    }};

    // Chargement de la texture
    auto const texture = gl::Texture{
        gl::TextureSource::File{
            .path           = "res/Crow.png",  // Chemin vers la texture
            .flip_y         = true, // Corrige l'orientation de la texture
            .texture_format = gl::InternalFormat::RGBA8,
        },
        gl::TextureOptions{
            .minification_filter  = gl::Filter::Linear,
            .magnification_filter = gl::Filter::Linear,
            .wrap_x               = gl::Wrap::Repeat,
            .wrap_y               = gl::Wrap::Repeat,
        }
    };

    // Chargement du shader
    auto const shader = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment.glsl"},
    }};

    glEnable(GL_DEPTH_TEST); // Active le test de profondeur

    while (gl::window_is_open()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        glm::mat4 view_matrix = camera.view_matrix();
        glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), gl::framebuffer_aspect_ratio(), 0.1f, 100.0f);
        glm::mat4 view_projection_matrix = projection_matrix * view_matrix;
        shader.set_uniform("view_projection_matrix", view_projection_matrix);

        // Passer la texture au shader
        shader.set_uniform("my_texture", texture);

        cube_mesh.draw();
    }
}
