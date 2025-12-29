#pragma once

/* Include */
// atlas
#include "basic.hpp"
#include "shaders.hpp"

/* Define */
namespace atlas::define {
    typedef uint64_t window_width;
    typedef uint64_t window_height;
}

/* Window */
namespace atlas::graphics {
    // window appearance data (NOT including inner window, opengl takes care of that)
    class window_styling {
    public:
        // window about
        std::string title;
        atlas::define::window_width width;
        atlas::define::window_height height;
        bool no_frame; // whether or not the borders and top bar of a window are showing
        bool resizable;

        // constructors
        window_styling() {
            title = "Default Window";
            width = 800;
            height = 600;
            no_frame = false;
            resizable = false;
        }
        window_styling(std::string _title, atlas::define::window_width _width, atlas::define::window_height _height, bool _no_frame) {
            title = _title;
            width = _width;
            height = _height;
            no_frame = _no_frame;
            resizable = false;
        }
    };

    // window
    class window {
    public:
        SDL_Window* window_context;
        SDL_GLContext sdl3_opengl_context;
        atlas::graphics::window_styling window_styling;

        window() {
            window_context = 0;
            sdl3_opengl_context = 0;
            window_styling = atlas::graphics::window_styling();
        }

        // open window
        atlas::error open(atlas::graphics::window_styling style) {
            // setup no error
            atlas::error output;

            // set styling
            window_styling = style;

            // setup opengl expectations
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

            // initalize window
            window_context = SDL_CreateWindow((const char*)style.title.c_str(), style.width, style.height, SDL_WINDOW_OPENGL/* | SDL_WINDOW_RESIZABLE*/);
            if (window_context == 0) {
                // return error
                return atlas::error(true, "{\"reason\": \"Failed to create SDL3 window context.\"}");
            }

            // initalize opengl context
            sdl3_opengl_context = SDL_GL_CreateContext(window_context);
            if (sdl3_opengl_context == 0) {
                // quit cleanly
                SDL_DestroyWindow(window_context);

                // return error
                return atlas::error(true, "{\"reason\": \"Failed to create OpenGL context.\"}");
            }

            // initalize glew
            GLenum glew_error = glewInit();
            if (glew_error != GLEW_OK) {
                // quit cleanly
                SDL_GL_DestroyContext(sdl3_opengl_context);
                SDL_DestroyWindow(window_context);

                // return error
                return atlas::error(true, "{\"reason\": \"GLEW did not initialize.\"}");
            }

            // setup clear color
            glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

            // window initilaized
            return output;
        }

        // close window
        void close() {
            // close graphics
            SDL_GL_DestroyContext(sdl3_opengl_context);
            SDL_DestroyWindow(window_context);
        }
    };
}
