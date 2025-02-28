#include "opengl-framework/opengl-framework.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main() {
    gl::init("3D Rendering with Render Target");
    gl::maximize_window();

    auto camera = gl::Camera{};
    gl::set_events_callbacks({camera.events_callbacks()});

    // 🟢 Création de la Render Target
    auto render_target = gl::RenderTarget{
        gl::RenderTarget_Descriptor{
            .width = gl::framebuffer_width_in_pixels(),
            .height = gl::framebuffer_height_in_pixels(),
            .color_textures = {
                gl::ColorAttachment_Descriptor{ .format = gl::InternalFormat_Color::RGBA8 }
            },
            .depth_stencil_texture = gl::DepthStencilAttachment_Descriptor{
                .format = gl::InternalFormat_DepthStencil::Depth32F
            }
        }
    };

    // 🟢 Gestion du redimensionnement de la fenêtre
    gl::set_events_callbacks({
        camera.events_callbacks(),
        {.on_framebuffer_resized = [&](gl::FramebufferResizedEvent const& e) {
            if (e.width_in_pixels != 0 && e.height_in_pixels != 0) {
                render_target.resize(e.width_in_pixels, e.height_in_pixels);
            }
        }},
    });

    // 🟢 Création du cube avec UVs
    auto const cube_mesh = gl::Mesh{
        {
            .vertex_buffers = {{
                .layout = {
                    gl::VertexAttribute::Position3D{0},
                    gl::VertexAttribute::UV{1}
                },
                .data = {
                    // Positions         // UVs
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f
                },
            }},
            .index_buffer = {
                0, 1, 2, 0, 2, 3,
                4, 5, 6, 4, 6, 7,
                4, 0, 3, 4, 3, 7,
                1, 5, 6, 1, 6, 2,
                3, 2, 6, 3, 6, 7,
                4, 5, 1, 4, 1, 0
            }
        }
    };

    // 🟢 Chargement de la texture pour le cube
    auto const texture = gl::Texture{
        gl::TextureSource::File{
            .path = "res/SnowMap.png",
            .flip_y = true,
            .texture_format = gl::InternalFormat::RGBA8
        },
        gl::TextureOptions{
            .minification_filter  = gl::Filter::Linear,
            .magnification_filter = gl::Filter::Linear,
            .wrap_x               = gl::Wrap::Repeat,
            .wrap_y               = gl::Wrap::Repeat
        }
    };

    // ✅ Shader de rendu 3D
    auto const scene_shader = gl::Shader{
        {
            .vertex = gl::ShaderSource::File{"res/vertex.glsl"},
            .fragment = gl::ShaderSource::File{"res/fragment.glsl"}
        }
    };

    // 🟢 Création du quad plein écran pour afficher la Render Target
    auto const screen_quad = gl::Mesh{
        {
            .vertex_buffers = {{
                .layout = { 
                    gl::VertexAttribute::Position2D{0}, 
                    gl::VertexAttribute::UV{1}
                },
                .data = {
                    -1.0f, -1.0f, 0.0f, 0.0f,
                     1.0f, -1.0f, 1.0f, 0.0f,
                     1.0f,  1.0f, 1.0f, 1.0f,
                    -1.0f,  1.0f, 0.0f, 1.0f
                },
            }},
            .index_buffer = { 0, 1, 2, 0, 2, 3 }
        }
    };

    // ✅ Shader pour le post-processing
    auto const postprocess_shader = gl::Shader{
        {
            .vertex = gl::ShaderSource::File{"res/screen_vertex.glsl"},
            .fragment = gl::ShaderSource::File{"res/postprocess.glsl"}
        }
    };

    glEnable(GL_DEPTH_TEST);

    while (gl::window_is_open()) {
        // 🎯 Rendu du cube dans la Render Target
        render_target.render([&]() {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            scene_shader.bind();
            glm::mat4 view_matrix = camera.view_matrix();
            glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), gl::framebuffer_aspect_ratio(), 0.1f, 100.0f);
            glm::mat4 view_projection_matrix = projection_matrix * view_matrix;
            scene_shader.set_uniform("view_projection_matrix", view_projection_matrix);
            scene_shader.set_uniform("my_texture", texture);

            cube_mesh.draw();
        });

        // 🖥️ Affichage de la Render Target sur l'écran
        glDisable(GL_DEPTH_TEST);
        postprocess_shader.bind();
        postprocess_shader.set_uniform("screen_texture", render_target.color_texture(0));
        screen_quad.draw();
        glEnable(GL_DEPTH_TEST);
    }
}
