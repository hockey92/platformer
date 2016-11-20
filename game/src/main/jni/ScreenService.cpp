//
// Created by qwerty on 25.09.16.
//

#include <GLES2/gl2.h>
#include "ScreenService.h"
#include "Shaders.h"
#include "TimeUtils.h"

ScreenService::ScreenService() : x(x), y(y) { }

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

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glLineWidth(1.5f);
}

void ScreenService::surfaceChanged(float w, float h) {
    glViewport(0, 0, w, h);
    physicalScreenSize = Vec2(w, h);
    calculateMVP();
}

Vec2 ScreenService::convertToGameCoordinates(float x, float y) {
    return Vec2(
            -1.f * mvp[15] + x / physicalScreenSize.x() * 2.f * mvp[15],
            1.f * mvp[15] / mvp[5] - y / physicalScreenSize.y() * 2.f * mvp[15] / mvp[5]
    );
}

void ScreenService::move(float x, float y) {
    this->x = x;
    this->y = y;
    calculateMVP();
}

void ScreenService::calculateMVP() {
    float rel = physicalScreenSize.x() / physicalScreenSize.y();

    float near = 2.0f;
    float far = 5.0f;

    float a = -(near + far) / (near - far);
    float b = -((2 * far * near) / (far - near));

    float temp[] = {
            1.f, 0.f, 0.f, 0.f,
            0.f, rel, 0.f, 0.f,
            0.f, 0.f, a, 1.f,
            x, y, b, 10.f
    };

    for (int i = 0; i < 16; i++) {
        mvp[i] = temp[i];
    }
}
