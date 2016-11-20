//
// Created by qwerty on 25.09.16.
//

#ifndef PLATFORMER_SCREENSERVICE_H
#define PLATFORMER_SCREENSERVICE_H

#include <vector>
#include "Map.h"
#include "BaseShape.h"
#include "Joint.h"
#include "DrawableShape.h"

class ScreenService {
public:
    ScreenService();

    void add(DrawableShape *shape);

    void draw();

    void surfaceChanged(float w, float h);

    void surfaceCreated();

    Vec2 convertToGameCoordinates(float x, float y);

    void move(float x, float y);

private:
    Map<float, std::vector<DrawableShape *> > shapesMap;
    float mvp[16];

    Vec2 physicalScreenSize;
    float x, y;

    void calculateMVP();
};

#endif //PLATFORMER_SCREENSERVICE_H
