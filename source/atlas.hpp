#pragma once

/* Include */
// atlas
#include "window.hpp"

/* Atlas */
namespace atlas {
    // atlas class
    class runner {
        // atlas is running
        bool running;

        // console popup menu
        atlas::graphics::window popup_menu;

    public:
        // atlas errors
        atlas::error error;

        // run atlas
        void run() {
            // init SDL3
            if (!SDL_Init(SDL_INIT_VIDEO)) {
                // setup error
                error = atlas::error(true, "{\"reason\": \"SDL3 did not initialize.\"}");

                printf("%s", (const char*)SDL_GetError());
                printf("\n");

                return;
            }

            // start runner
            running = true;

            // open menu
            popup_menu = atlas::graphics::window();
            error = popup_menu.open(atlas::graphics::window_styling("Menu", 1280, 1080, false));

            // check for error
            if (error.occured) {
                return;
            }

            // runner loop
            while (running) {
                // event temp
                SDL_Event event;

                // poll events
                while (SDL_PollEvent(&event)) {
                    // check for quit
                    if (event.type == SDL_EVENT_QUIT) {
                        // close window
                        running = false;
                    }
                }

                // clear buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // display window
                SDL_GL_SwapWindow(popup_menu.window_context);
            }

            // close menu
            popup_menu.close();

            // close SDL3
            SDL_Quit();
        }
    };
}
