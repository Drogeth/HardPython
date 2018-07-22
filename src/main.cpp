#include <iostream>
#include <ctime>
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "core/window.h"
#include "core/input.h"

int main(int argc, char *argv[]) {
    // Initialize SDL and OpenGL
    minalear::init_game_window(800, 450);
    minalear::init_opengl();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Setup controller input
    minalear::init_input();
    auto gamepad = minalear::get_controller_ptr();

    // Improved fixed update functions
    double time_accumulator = 0.f;

    // Begin main game loop
    SDL_Event windowEvent;
    while(true) {
        if (SDL_PollEvent(&windowEvent)) {
            // Signal to close window, break out of game loop
            if (windowEvent.type == SDL_QUIT) break;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        minalear::handle_input();


        // Accumulate time and call update_fixed if past threshold (16ms = 60fps)
        time_accumulator += minalear::dt();

        const float CONST_DT = 0.016f; // 16ms
        if (time_accumulator >= CONST_DT) {
            // screen_manager.update_fixed(CONST_DT);
            time_accumulator = 0.f;
        }

        minalear::swap_buffers();
        if (minalear::was_button_up(minalear::JOYSTICK_BUTTONS::A)) {
            std::cout << "W";
        }

        SDL_FlushEvent(SDL_JOYAXISMOTION);
    } // end main game loop

    minalear::finalize_window();
    return 0;
}