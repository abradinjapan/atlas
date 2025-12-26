#pragma once

/* Include */
// c++
#include "includes.hpp"

// atlas
#include "window.hpp"
#include "input.hpp"

/* Atlas */
namespace atlas {
    // atlas class
    class runner {
        // atlas is running
        bool running;

        // console popup menu
        atlas::graphics::window popup_menu;

        // input devices
        atlas::input::devices input_devices;

    public:
        // atlas errors
        atlas::error error;

        // run atlas
        void run() {
            // init SDL3
            if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD)) {
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
            error = popup_menu.open(atlas::graphics::window_styling("Menu", 800, 600, false));

            // check for error
            if (error.occured) {
                return;
            }

            // event temps
            SDL_Event event;

            // runner loop
            while (running) {
                // poll events
                while (SDL_PollEvent(&event)) {
                    // check event
                    switch (event.type) {
                    // check for quit
                    case SDL_EVENT_QUIT:
                        // close window
                        running = false;

                        break;
                    // check for gamepad added and handle accordingly
                    case SDL_EVENT_GAMEPAD_ADDED:
                        // DEBUG
                        std::cout << "Controller Added!" << std::endl;

                        // open pad
                        input_devices.add_controller(atlas::input::controller(event.gdevice.which));

                        break;
                    // check for gamepad removed and handle accordingly
                    case SDL_EVENT_GAMEPAD_REMOVED:
                        // DEBUG
                        std::cout << "Controller Removed!" << std::endl;

                        // close pad
                        input_devices.remove_controller_by_gamepad(SDL_GetGamepadFromID(event.gdevice.which));

                        break;
                    // check for gamepad button pressed
                    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                        // check for guide button pressed
                        if (event.gbutton.button == SDL_GAMEPAD_BUTTON_GUIDE) {
                            // set clear color to white
                            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                        }
                        break;
                    // do nothing for unhandled event
                    default:
                        break;
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
