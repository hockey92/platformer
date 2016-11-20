//
// Created by qwerty on 13.11.16.
//

#ifndef PLATFORMER_CUBE_H
#define PLATFORMER_CUBE_H

#include "VertexBuff.h"

class Cube {
public:
    Cube(float x, float y, float z);

    void init();

    void draw(float *mvp);

private:
    VertexBuff *vertexBuff;
    float x, y, z;
};


#endif //PLATFORMER_CUBE_H
