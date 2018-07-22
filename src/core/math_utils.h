//
// Created by Trevor Fisher on 2/21/2018.
//

#ifndef MINALEAR_MATH_UTILS_H
#define MINALEAR_MATH_UTILS_H

#include "glm.hpp"

namespace minalear {
    int rand_int(int min, int max);
    float rand_float(float min, float max);
    float distance(glm::vec2 a, glm::vec2 b);
    float distance_square(glm::vec2 a, glm::vec2 b);
}

#endif //MINALEAR_MATH_UTILS_H
