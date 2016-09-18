//
// Created by qwerty on 18.09.16.
//

#ifndef PLATFORMER_RECTANGLEPHYSICSOBJECT_H
#define PLATFORMER_RECTANGLEPHYSICSOBJECT_H


#include "PhysicsObject.h"

class RectanglePhysicsObject : public PhysicsObject {
public:
    RectanglePhysicsObject(float w, float h, float invM);
};


#endif //PLATFORMER_RECTANGLEPHYSICSOBJECT_H
