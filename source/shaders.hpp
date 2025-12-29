#pragma once

/* Include */
// atlas
#include "basic.hpp"

/* Shaders */
namespace atlas::graphics {
    // constants
    const atlas::u64 opengl_error_log_max_length = 2048;

    // one shader
    class shader {
    public:
        // shader data
        GLuint shader_ID;
        std::string code;

        // error data
        std::string opengl_log;
        GLint opengl_log_length;
        GLenum opengl_error_code;

        // constructor
        shader() {
            shader_ID = 0;
            code = "";
            opengl_log = "";
            opengl_log_length = 0;
            opengl_error_code = GL_NO_ERROR;
        }

        // open and compile shader
        shader(std::string _code, atlas::error* _error, GLenum _shader_type) {
            // create new shader
            shader_ID = glCreateShader(_shader_type);

            // send source code to gpu
            glShaderSource(shader_ID, 1, (const GLchar* const*)_code.c_str(), NULL);

            // compiler the shader
            glCompileShader(shader_ID);

            // check for opengl errors
            glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &opengl_log_length);
            if (opengl_log_length > 0) {
                // create place for opengl to dump log
                atlas::character log[opengl_error_log_max_length];

                // get opengl error data
                glGetShaderInfoLog(shader_ID, atlas::graphics::opengl_error_log_max_length, NULL, (GLchar*)&log);
                opengl_error_code = glGetError();

                // convert log error to string
                opengl_log = std::string((char*)&log, opengl_log_length);

                // generate atlas error
                if (_shader_type == GL_VERTEX_SHADER) {
                    *_error = atlas::error(true, "{\n\t\"reason\": \"OpenGL vertex shader did not compile.\",\n\t\"OpenGL Error Code\": " + std::to_string((int)opengl_error_code) + ",\n\t\"OpenGL Log\": \"" + opengl_log + "\"\n}");
                } else if (_shader_type == GL_FRAGMENT_SHADER) {
                    *_error = atlas::error(true, "{\n\t\"reason\": \"OpenGL fragment shader did not compile.\",\n\t\"OpenGL Error Code\": " + std::to_string((int)opengl_error_code) + ",\n\t\"OpenGL Log\": \"" + opengl_log + "\"\n}");
                }
            }

            return;
        }

        // close shader
        ~shader() {
            glDeleteShader(shader_ID);
        }
    };

    // one shader program
    class shaders {
    public:
        // shader program data
        GLuint program_ID;
        atlas::graphics::shader vertex_shader;
        atlas::graphics::shader fragment_shader;

        // error data
        std::string opengl_log;
        GLint opengl_log_length;
        GLenum opengl_error_code;

        // constructors
        shaders(atlas::error* _error, std::string _vertex_shader, std::string _fragment_shader) {
            // compile vertex shader
            vertex_shader = atlas::graphics::shader(_vertex_shader, _error, GL_VERTEX_SHADER);
            if ((*_error).occured) {
                return;
            }

            // compile fragment shader
            fragment_shader = atlas::graphics::shader(_fragment_shader, _error, GL_FRAGMENT_SHADER);
            if ((*_error).occured) {
                return;
            }

            // create shader program
            program_ID = glCreateProgram();

            // setup shader linking
            glAttachShader(program_ID, vertex_shader.shader_ID);
            glAttachShader(program_ID, fragment_shader.shader_ID);

            // link shaders
            glLinkProgram(program_ID);

            // check for opengl errors
            glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &opengl_log_length);
            if (opengl_log_length > 0) {
                // create place for opengl to dump log
                atlas::character log[opengl_error_log_max_length];
                
                // get opengl error data
                glGetProgramInfoLog(program_ID, atlas::graphics::opengl_error_log_max_length, NULL, (GLchar*)&log);
                opengl_error_code = glGetError();

                // convert log error to string
                opengl_log = std::string((char*)&log, opengl_log_length);

                // generate atlas error
                *_error = atlas::error(true, "{\n\t\"reason\": \"OpenGL shaders did not link together.\",\n\t\"OpenGL Error Code\": " + std::to_string((int)opengl_error_code) + ",\n\t\"OpenGL Log\": \"" + opengl_log + "\"\n}");
            }
        }

        // use shader program
        void use_program() {
            glUseProgram(program_ID);
        }

        // close shaders
        ~shaders() {
            // close individual shaders
            vertex_shader.~shader();
            fragment_shader.~shader();

            // close shader program
            glDeleteProgram(program_ID);
        }
    };
}
