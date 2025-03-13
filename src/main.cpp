#include "opengl-framework/opengl-framework.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <tiny_obj_loader.h>
#include <filesystem>
#include <vector>
#include <iostream>
#include "glm/ext/matrix_transform.hpp"

auto load_mesh(std::filesystem::path const& path) -> gl::Mesh {
    tinyobj::ObjReader reader;
    reader.ParseFromFile(gl::make_absolute_path(path).string(), {});

    std::vector<float> vertices;
    for (auto const& shape : reader.GetShapes()) {
        for (auto const& idx : shape.mesh.indices) {
            // Position (X, Y, Z)
            vertices.push_back(reader.GetAttrib().vertices[3 * idx.vertex_index + 0]);
            vertices.push_back(reader.GetAttrib().vertices[3 * idx.vertex_index + 1]);
            vertices.push_back(reader.GetAttrib().vertices[3 * idx.vertex_index + 2]);

            // UV (U, V)
            vertices.push_back(reader.GetAttrib().texcoords[2 * idx.texcoord_index + 0]);
            vertices.push_back(1.0f - reader.GetAttrib().texcoords[2 * idx.texcoord_index + 1]); // Flip Y

                        // Normale
            vertices.push_back(reader.GetAttrib().normals[3 * idx.normal_index + 0]);
            vertices.push_back(reader.GetAttrib().normals[3 * idx.normal_index + 1]);
            vertices.push_back(reader.GetAttrib().normals[3 * idx.normal_index + 2]);
        }
    }

    // Création du mesh
    return gl::Mesh{{
        .vertex_buffers = {{
            .layout = {
                gl::VertexAttribute::Position3D{0},
                gl::VertexAttribute::UV{1},
                gl::VertexAttribute::Normal3D{2}
            },
            .data = vertices
        }}
    }};
}

int main() {
    gl::init("3D Model Rendering");
    gl::maximize_window();

    auto camera = gl::Camera{};
    gl::set_events_callbacks({camera.events_callbacks()});

    auto const model_mesh = load_mesh("res/model.obj");

    auto const texture = gl::Texture{
        gl::TextureSource::File{
            .path = "res/fourareen2K_albedo.jpg",
            .flip_y = false,
            .texture_format = gl::InternalFormat::RGBA8
        },
        gl::TextureOptions{
            .minification_filter  = gl::Filter::Linear,
            .magnification_filter = gl::Filter::Linear,
            .wrap_x               = gl::Wrap::Repeat,
            .wrap_y               = gl::Wrap::Repeat
        }
    };

    auto const scene_shader = gl::Shader{
        {
            .vertex = gl::ShaderSource::File{"res/vertex.glsl"},
            .fragment = gl::ShaderSource::File{"res/fragment.glsl"}
        }
    };

    glEnable(GL_DEPTH_TEST);

    while (gl::window_is_open()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        scene_shader.bind();
    
        glm::mat4 view_matrix = camera.view_matrix();
        glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), gl::framebuffer_aspect_ratio(), 0.1f, 100.0f);
        
        glm::mat4 const rotation = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds(), glm::vec3{1.f, 0.f, 0.f});
        
        glm::mat4 view_projection_matrix = projection_matrix * view_matrix * rotation;
        glm::mat4 normal_matrix = glm::transpose(glm::inverse(rotation));
    
        scene_shader.set_uniform("view_projection_matrix", view_projection_matrix);
        scene_shader.set_uniform("normal_matrix", normal_matrix);
        scene_shader.set_uniform("my_texture", texture);
    
        glm::vec3 light_dir = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
        scene_shader.set_uniform("light_direction", light_dir);
    
        model_mesh.draw();
    }
    
}