//
// Created by Trevor Fisher on 7/26/2018.
//

#ifndef HARD_PYTHON_SHAPE_RENDERER_H
#define HARD_PYTHON_SHAPE_RENDERER_H

#include "glm.hpp"
#include "../core/shader_program.h"

class shape_renderer {
private:

    uint32_t vao, vbo;
    float *buffer_data;

    void draw_vertices(int num_verts, int vbo_index);

public:
    shape_renderer();
    ~shape_renderer();

    void draw_circle(minalear::shader_program *shader, glm::vec2 position, float scale, glm::vec3 color);
    void draw_circle(minalear::shader_program *shader, glm::vec2 position, glm::vec2 scale, glm::vec3 color);
    void draw_rectangle(minalear::shader_program *shader, glm::vec2 position, glm::vec2 size, glm::vec3 color);
};


#endif //HARD_PYTHON_SHAPE_RENDERER_H
