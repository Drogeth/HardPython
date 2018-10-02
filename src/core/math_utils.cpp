//
// Created by Trevor Fisher on 2/21/2018.
//

#include "math_utils.h"
#include <random>

// generates random ints to be used
int minalear::rand_int(int min, int max) {
    return (int)((rand() / (float)RAND_MAX) * (max - min) + min);
}

// generates random floats to be used
float minalear::rand_float(float min, float max) {
    return (rand() / (float)RAND_MAX) * (max - min) + min;
}
// gets the distance of objects and returns it
float minalear::distance(glm::vec2 a, glm::vec2 b) {
    return sqrtf(distance_square(a, b));
}
// finds the distance to be returned to distance function
float minalear::distance_square(glm::vec2 a, glm::vec2 b) {
    float x_sqr = (b.x - a.x) * (b.x - a.x);
    float y_sqr = (b.y - a.y) * (b.y - a.y);

    return x_sqr + y_sqr;
}
