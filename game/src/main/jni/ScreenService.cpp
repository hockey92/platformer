//
// Created by qwerty on 25.09.16.
//

#include <GLES2/gl2.h>
#include "ScreenService.h"
#include "Shaders.h"
#include "RectanglePhysicsObject.h"
#include "Joint.h"

ScreenService::ScreenService() {
    child = (new RectanglePhysicsObject(2, 0.5f, 0))->getShape();
    parent = (new RectanglePhysicsObject(2, 0.5f, 0))->getShape();

    parent->rotate(PI /4);
    parent->move(Vec2(1, 1));

    add(child);
    add(parent);

    joint = new Joint(parent,
                             PolarCoords(0, 1),
                             child,
                             PolarCoords(PI, 1));
    joint->setAngleBetweenPArentAndChild(PI - 0.5f);
    joint->update();
}


void ScreenService::add(BaseShape *shape) {
    std::vector<BaseShape *> *shapes = shapesMap.get(shape->getZ());
    if (shapes == NULL) {
        shapes = shapesMap.put(shape->getZ(), std::vector<BaseShape *>());
    }
    shapes->push_back(shape);
}

void ScreenService::draw() {

    parent->rotate(0.01f);

    joint->setAngleBetweenPArentAndChild(joint->getAngleBetweenParentAndChild() + 0.01f);
    joint->update();

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    Iterator<float, std::vector<BaseShape *> > it = shapesMap.getIterator();
    while (it.hasNext()) {
        std::pair<const float, std::vector<BaseShape *> > *next = it.next();
        for (int i = 0; i < next->second.size(); i++) {
            next->second[i]->draw(mvp);
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
