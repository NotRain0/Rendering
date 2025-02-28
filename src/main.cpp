#include "opengl-framework/opengl-framework.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp> 

int main() {
    gl::init("3D Rendering");
    gl::maximize_window();

    auto camera = gl::Camera{};
    gl::set_events_callbacks({camera.events_callbacks()});

    auto const rectangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position3D{0}},
            .data = {
                -0.5f, -0.5f, 0.0f, // Premier sommet (ajouté une coordonnée z)
                0.5f, -0.5f, 0.0f,  // Deuxième sommet
                0.5f, 0.5f, 0.0f,   // Troisième sommet
                -0.5f, 0.5f, 0.0f   // Quatrième sommet
            },
        }},
        .index_buffer = {
            0, 1, 2,
            0, 2, 3
        },
    }};

    auto const shader = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment.glsl"},
    }};

    glEnable(GL_DEPTH_TEST); // Activer le test de profondeur

    while (gl::window_is_open()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        glm::mat4 view_matrix = camera.view_matrix();
        glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), gl::framebuffer_aspect_ratio(), 0.1f, 100.0f);
        glm::mat4 view_projection_matrix = projection_matrix * view_matrix;
        shader.set_uniform("view_projection_matrix", view_projection_matrix);

        rectangle_mesh.draw();
    }
}
