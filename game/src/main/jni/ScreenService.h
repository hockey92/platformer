//
// Created by qwerty on 25.09.16.
//

#ifndef PLATFORMER_SCREENSERVICE_H
#define PLATFORMER_SCREENSERVICE_H

#include <vector>
#include "Map.h"
#include "BaseShape.h"
#include "Joint.h"

class ScreenService {
public:
    ScreenService();

    void add(BaseShape *shape);

    void draw();

    void surfaceChanged(float w, float h);

    void surfaceCreated();

private:
    Map<float, std::vector<BaseShape *> > shapesMap;
    float mvp[16];

    Vec2 physicalScreenSize;
};

#endif //PLATFORMER_SCREENSERVICE_H
