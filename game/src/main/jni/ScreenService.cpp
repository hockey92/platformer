//
// Created by qwerty on 25.09.16.
//

#include <GLES2/gl2.h>
#include "ScreenService.h"
#include "Shaders.h"
#include "TimeUtils.h"

ScreenService::ScreenService() { }

void ScreenService::add(DrawableShape *shape) {
    std::vector<DrawableShape *> *shapes = shapesMap.get(shape->getZ());
    if (shapes == NULL) {
        shapes = shapesMap.put(shape->getZ(), std::vector<DrawableShape *>());
    }
    shapes->push_back(shape);
}

void ScreenService::draw() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    Iterator<float, std::vector<DrawableShape *> > it = shapesMap.getIterator();
    while (it.hasNext()) {
        std::pair<const float, std::vector<DrawableShape *> > *next = it.next();
        for (int i = 0; i < next->second.size(); i++) {
            double time = TimeUtils::now();
            if (next->second[i]->isVisible()) {
                next->second[i]->draw(mvp);
            }
//            LOGE("draw time %f", TimeUtils::now() - time);
        }
    }
}

void ScreenService::surfaceCreated() {
    Shaders::compile();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glLineWidth(1.5f);
}

void ScreenService::surfaceChanged(float w, float h) {
    glViewport(0, 0, w, h);

    physicalScreenSize = Vec2(w, h);

    for (int i = 0; i < 16; i++) {
        mvp[i] = 0;
    }

    float rel = w / h;

    mvp[0] = 1.0f;
    mvp[5] = rel;
    mvp[10] = 1.0f;
    mvp[15] = 10.0f;
}

Vec2 ScreenService::convertToGameCoordinates(float x, float y) {
    return Vec2(
            -1.f * mvp[15] + x / physicalScreenSize.x() * 2.f * mvp[15],
            1.f * mvp[15] / mvp[5] - y / physicalScreenSize.y() * 2.f * mvp[15] / mvp[5]
    );
}
