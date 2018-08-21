//
// Created by Trevor Fisher on 8/20/2018.
//

#ifndef HARD_PYTHON_TILEMAP_RENDERER_H
#define HARD_PYTHON_TILEMAP_RENDERER_H

#include "glm.hpp"
#include "../core/shader_program.h"
#include "../game/level.h"


class tilemap_renderer {
private:
    uint32_t vao, vbo;
    float *buffer_data;

public:
    tilemap_renderer(level &map);
    ~tilemap_renderer();

    void draw_map(minalear::shader_program *shader, glm::vec2 position, glm::vec2 scale);
};


#endif //HARD_PYTHON_TILEMAP_RENDERER_H
