#pragma once

/* Include */
// dependencies
#include "includes.hpp"

// atlas
#include "error.hpp"

/* Controllers */
namespace atlas::input {
    // types
    typedef uint64_t controller_ID;
    const controller_ID invalid_controller_ID = -1;

    // controller
    class controller {
    public:
        SDL_Gamepad* gamepad;

        // constructors
        controller() {
            gamepad = 0;
        }
        controller(SDL_JoystickID _event_device_data) {
            gamepad = SDL_OpenGamepad(_event_device_data);
        }
        
        // open controller
        void open(SDL_JoystickID _event_device_data) {
            gamepad = SDL_OpenGamepad(_event_device_data);
        }

        // close controller
        void close() {
            SDL_CloseGamepad(gamepad);
        }
    };

    // all user input devices
    class devices {
    public:
        std::vector<atlas::input::controller> controllers;

        // find controller by gamepad
        atlas::input::controller_ID find_controller_ID_by_gamepad(SDL_Gamepad* _gamepad) {
            // search
            for (controller_ID index = 0; index < controllers.size(); index++) {
                if (controllers[index].gamepad == _gamepad) {
                    return index;
                }
            }

            return 0;
        }

        // add controller
        controller_ID add_controller(atlas::input::controller _controller) {
            // append controller if open
            if (_controller.gamepad) {
                controllers.push_back(_controller);

                // return ID
                return controllers.size();
            // controller isn't valid
            } else {
                return atlas::input::invalid_controller_ID;
            }
        }

        // remove controller
        void remove_controller(atlas::input::controller_ID _controller_ID) {
            // close controller
            controllers[_controller_ID].close();

            // remove controller
            controllers.erase(controllers.begin() + _controller_ID);
        }

        // remove controller by gamepad
        void remove_controller_by_gamepad(SDL_Gamepad* _gamepad) {
            // get controller
            atlas::input::controller_ID temp = find_controller_ID_by_gamepad(_gamepad);

            // remove controller
            remove_controller(temp);
        }
    };
}
