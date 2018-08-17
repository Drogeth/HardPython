//
// Created by Trevor Fisher on 7/26/2018.
//

#include "shape_renderer.h"
#include "gtc/matrix_transform.hpp"
#include <cmath>

struct shape {
    float* vertex_data;
};

const float TWO_PI = 3.14159f * 2.f;

const int NUM_CIRCLE_VERTS = 32;
const int NUM_RECT_VERTS = 4;

shape_renderer::shape_renderer() {
    int total_number_verts = NUM_CIRCLE_VERTS + NUM_RECT_VERTS;
    buffer_data = new float[total_number_verts * 5];

    // Init buffer_data to 1.f
    for (int i = 0; i < total_number_verts * 5; i++) {
        buffer_data[i] = 1.f;
    }

    // Generate circle shape
    for (int i = 0; i < NUM_CIRCLE_VERTS; i++) {
        float x = cosf(TWO_PI * (i / (float)NUM_CIRCLE_VERTS));
        float y = sinf(TWO_PI * (i / (float)NUM_CIRCLE_VERTS));

        buffer_data[i * 5 + 0] = x;
        buffer_data[i * 5 + 1] = y;
    }

    // Generate rectangle shape

    buffer_data[NUM_CIRCLE_VERTS * 5 + 0] = 0.f;
    buffer_data[NUM_CIRCLE_VERTS * 5 + 1] = 0.f;

    buffer_data[NUM_CIRCLE_VERTS * 5 + 5] = 0.f;
    buffer_data[NUM_CIRCLE_VERTS * 5 + 6] = 1.f;

    buffer_data[NUM_CIRCLE_VERTS * 5 + 10] = 1.f;
    buffer_data[NUM_CIRCLE_VERTS * 5 + 11] = 1.f;

    buffer_data[NUM_CIRCLE_VERTS * 5 + 15] = 1.f;
    buffer_data[NUM_CIRCLE_VERTS * 5 + 16] = 0.f;

    // VAO and VBO init
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * total_number_verts * 5, buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Color

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
shape_renderer::~shape_renderer() {
    delete buffer_data;
}

void shape_renderer::draw_vertices(int num_vertices, int offset) {
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, offset, num_vertices);
    glBindVertexArray(0);
}

void shape_renderer::draw_circle(minalear::shader_program *shader, glm::vec2 position, float scale, glm::vec3 color) {
    shader->use();
    auto model =
            glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(scale, scale, 1.f));
    shader->set_model_mat4(model);

    draw_vertices(NUM_CIRCLE_VERTS, 0);
}

void shape_renderer::draw_circle(minalear::shader_program *shader, glm::vec2 position, glm::vec2 scale, glm::vec3 color) {
    shader->use();
    auto model =
            glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(scale, 1.f));
    shader->set_model_mat4(model);

    draw_vertices(NUM_CIRCLE_VERTS, 0);
}

void shape_renderer::draw_rectangle(minalear::shader_program *shader, glm::vec2 position, glm::vec2 size, glm::vec3 color) {
    shader->use();
    auto model =
            glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(size, 1.f));
    shader->set_model_mat4(model);

    draw_vertices(NUM_RECT_VERTS, NUM_CIRCLE_VERTS);
}
