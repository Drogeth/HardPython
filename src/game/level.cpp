//
// Created by Trevor Fisher on 8/17/2018.
//

#include "level.h"

level_layer::level_layer() {
    width = 0;
    height = 0;
}
level_layer::~level_layer() {
    delete data;
}

level::level() {
    width = 0;
    height = 0;
    tileWidth = 0;
    tileHeight = 0;
}
level::~level() {
    delete layers;
}