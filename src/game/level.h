//
// Created by Trevor Fisher on 8/17/2018.
//

#ifndef HARD_PYTHON_LEVEL_H
#define HARD_PYTHON_LEVEL_H

class level_layer {
public:
    int width;
    int height;

    int *data;

    level_layer();
    ~level_layer();
};

class level {
public:
    int width;
    int height;
    int tileWidth;
    int tileHeight;

    level_layer *layers;

    level();
    ~level();
};

#endif //HARD_PYTHON_LEVEL_H
