// c++
#include <iostream>

// atlas
#include "atlas.hpp"

int main() {
    // hello console
    std::cout << "Starting Atlas!" << std::endl;

    // force x11 over wayland
    setenv("SDL_VIDEODRIVER", "x11", 1);

    // run atlas
    atlas::runner atlas;
    atlas.run();

    std::cout << atlas.error.json << std::endl;
}
