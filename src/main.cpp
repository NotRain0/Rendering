#include "opengl-framework/opengl-framework.hpp"


int main()
{
    // Initialisation
    gl::init("TPs de Rendering"); 
    gl::maximize_window(); 

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
    
        rectangle_mesh.draw();
    }
}