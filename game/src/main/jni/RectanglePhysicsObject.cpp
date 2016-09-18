//
// Created by qwerty on 18.09.16.
//

#include "RectanglePhysicsObject.h"
#include "PolygonShape.h"

RectanglePhysicsObject::RectanglePhysicsObject(float w, float h, float invM) {
    Vec2 vertices2[] = {Vec2(w / 2, h / 2),
                        Vec2(-w / 2, h / 2),
                        Vec2(-w / 2, -h / 2),
                        Vec2(w / 2, -h / 2)};
    setShape(new PolygonShape(vertices2, 4));
    setInvM(invM);
    setInvI(invM > 0 ? 12.0f * invM / (w * w + h * h) : 0);
}
