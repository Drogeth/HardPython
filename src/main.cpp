#include <iostream>
#include <ctime>
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "core/window.h"
#include "core/input.h"
#include "core/shader_program.h"
#include "core/file_handler.h"
#include "core/texture.h"
#include "renderers/shape_renderer.h"
#include "renderers/tilemap_renderer.h"
#include "game/level.h"

int main(int argc, char *argv[]) {
    // Initialize SDL and OpenGL
    minalear::init_game_window(800, 450);
    minalear::init_opengl();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    level test_level;

    uint32_t fileSize = 0;
    uint8_t *level_data = (uint8_t*)minalear::read_binary_file("content/level.bin", fileSize);

    // Meta info block (skip first four bytes)
    test_level.width = uint32_t(
            level_data[5] << 8 |
            level_data[4]
    );
    test_level.height = uint32_t(
            level_data[7] << 8 |
            level_data[6]
    );

    test_level.tileWidth = level_data[8];
    test_level.tileHeight = level_data[9];
    test_level.layer_count = level_data[10];
    test_level.layers = new level_layer[test_level.layer_count];

    // Layer block
    int index_ptr = 11;
    for (int i = 0; i < test_level.layer_count; i++) {
        index_ptr += 4; // width, height

        // Calculate the layer data block size by multiplying the map width by height
        int data_block_size = test_level.width * test_level.height;
        test_level.layers[i].data = new int[data_block_size];

        // Load in the data from the buffer
        for (int k = 0; k < data_block_size; k++) {
            int id = level_data[index_ptr++];
            test_level.layers[i].data[k] = id;
        }
    }

    delete level_data;

    // Setup debug shader
    /*auto shader = new minalear::shader_program(
            minalear::read_file("shaders/basic_vert.glsl"),
            minalear::read_file("shaders/basic_frag.glsl"));
    shader->use();
    shader->init_uniforms();*/

    auto shader = new minalear::shader_program(
            minalear::read_file("shaders/text_vert.glsl"),
            minalear::read_file("shaders/text_frag.glsl"));
    shader->use();
    shader->init_uniforms();

    // Initialize matrices
    glm::mat4 proj, view, model;
    proj  = glm::ortho(0.f, 800.f, 450.f, 0.f, -10.f, 10.f);
    view  = glm::mat4(1.f);
    model = glm::mat4(1.f);

    shader->set_proj_mat4(proj);
    shader->set_view_mat4(view);
    shader->set_model_mat4(model);

    //shape_renderer renderer;
    tilemap_renderer renderer(test_level);

    minalear::texture tileset("content/tileset.png");

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

        float camera_zoom = 1.f;
        auto cam_pos = glm::vec2(0.f, 0.f);

        if (gamepad->left_stick_length > 0.25f) {
            camera_zoom += (gamepad->left_stick_length - 0.25f) * 100.f;
        }

        view = glm::translate(glm::mat4(1.f), glm::vec3(400.f, 225.f, 0.f)) *
               glm::scale(glm::mat4(1.f), glm::vec3(camera_zoom)) *
               glm::translate(glm::mat4(1.f), glm::vec3(cam_pos, 0.f));

        shader->use();
        shader->set_view_mat4(view);

        tileset.bind();

        /*renderer.draw_circle(shader, glm::vec2(0.f, 0.f), 80.f, glm::vec3(1.f, 1.f, 1.f));
        renderer.draw_circle(shader, glm::vec2(0.f, 0.f), glm::vec2(80.f, 120.f), glm::vec3(1.f));
        renderer.draw_circle(shader, glm::vec2(0.f, 0.f), glm::vec2(120.f, 80.f), glm::vec3(1.f));
        renderer.draw_rectangle(shader, glm::vec2(-120.f), glm::vec2(240.f), glm::vec3(1.f));*/

        renderer.draw_map(shader, glm::vec2(0.f, 0.f), glm::vec2(1.f));

        minalear::handle_input();

        // Accumulate time and call update_fixed if past threshold (16ms = 60fps)
        time_accumulator += minalear::dt();

        const float CONST_DT = 0.016f; // 16ms
        if (time_accumulator >= CONST_DT) {
            // screen_manager.update_fixed(CONST_DT);
            time_accumulator = 0.f;
        }

        minalear::swap_buffers();
        SDL_FlushEvent(SDL_JOYAXISMOTION);
    } // end main game loop

    delete shader;
    minalear::finalize_window();
    return 0;
}