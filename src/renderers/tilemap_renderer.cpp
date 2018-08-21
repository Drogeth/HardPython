//
// Created by Trevor Fisher on 8/20/2018.
//

#include "tilemap_renderer.h"
#include "gtc/matrix_transform.hpp"

tilemap_renderer::tilemap_renderer(level &map) {
    const int num_tiles = map.width * map.height * map.layer_count;
    const int total_verts = num_tiles * 6;
    buffer_data = new float[total_verts * 8];

    // Init all buffer data to 1.f
    for (int i = 0; i < total_verts * 7; i++) {
        buffer_data[i] = 1.f;
    }

    // Generate vertices for the tilemap (top-left to bottom-right)
    for (int layer = 0; layer < map.layer_count; layer++) {
        for (int i = 0; i < map.width * map.height; i++) {
            int x = i % map.width;
            int y = i / map.width;

            int tile_id = map.layers[layer].data[i] - 1;
            if (tile_id == -1) continue;

            float tile_size = (1.f / 8.f);
            float tile_x = (tile_id % 8) * tile_size;
            float tile_y = (tile_id / 8) * tile_size;


            // Top Left
            buffer_data[i * 48 + 0] = x * map.tileWidth; // X
            buffer_data[i * 48 + 1] = y * map.tileHeight; // Y
            buffer_data[i * 48 + 2] = layer; // Depth

            buffer_data[i * 48 + 3] = tile_x; // uX
            buffer_data[i * 48 + 4] = tile_y; // uY


            // Bot Left
            buffer_data[i * 48 + 8] = x * map.tileWidth; // X
            buffer_data[i * 48 + 9] = y * map.tileHeight + map.tileHeight; // Y
            buffer_data[i * 48 + 10] = layer; // Depth

            buffer_data[i * 48 + 11] = tile_x; // uX
            buffer_data[i * 48 + 12] = tile_y + tile_size; // uY


            // Top Right
            buffer_data[i * 48 + 16] = x * map.tileWidth + map.tileWidth; // X
            buffer_data[i * 48 + 17] = y * map.tileHeight; // Y
            buffer_data[i * 48 + 18] = layer; // Depth

            buffer_data[i * 48 + 19] = tile_x + tile_size; // uX
            buffer_data[i * 48 + 20] = tile_y; // uY



            // Top Right
            buffer_data[i * 48 + 24] = x * map.tileWidth + map.tileWidth; // X
            buffer_data[i * 48 + 25] = y * map.tileHeight; // Y
            buffer_data[i * 48 + 26] = layer; // Depth

            buffer_data[i * 48 + 27] = tile_x + tile_size; // uX
            buffer_data[i * 48 + 28] = tile_y; // uY


            // Bot Left
            buffer_data[i * 48 + 32] = x * map.tileWidth; // X
            buffer_data[i * 48 + 33] = y * map.tileHeight + map.tileHeight; // Y
            buffer_data[i * 48 + 34] = layer; // Depth

            buffer_data[i * 48 + 35] = tile_x; // uX
            buffer_data[i * 48 + 36] = tile_y + tile_size; // uY


            // Bot Right
            buffer_data[i * 48 + 40] = x * map.tileWidth + map.tileWidth; // X
            buffer_data[i * 48 + 41] = y * map.tileHeight + map.tileHeight; // Y
            buffer_data[i * 48 + 42] = layer; // Depth

            buffer_data[i * 48 + 43] = tile_x + tile_size; // uX
            buffer_data[i * 48 + 44] = tile_y + tile_size; // uY
        }
    }

    // VAO and VBO init
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * total_verts * 8, buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // UV
    glEnableVertexAttribArray(2); // Color

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

tilemap_renderer::~tilemap_renderer() {
    delete buffer_data;
}

void tilemap_renderer::draw_map(minalear::shader_program *shader, glm::vec2 position, glm::vec2 scale) {
    const int NUM_TILES = 18 * 25 * 2;

    auto model =
            glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(scale, 1.f));
    shader->set_model_mat4(model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, NUM_TILES * 6);
    glBindVertexArray(0);
}
