#ifndef NATIVE_ACTIVITY_COLLISION_H
#define NATIVE_ACTIVITY_COLLISION_H

#include <math.h>
#include "Vec2.h"

class Collision {

public:
    Collision(const Vec2 &normal, const Vec2 &r1, const Vec2 &r2, float dist) :
            _normal(normal),
            _tangent(Vec2(normal.y(), -normal.x())),
            _r1(r1),
            _r2(r2),
            _dist(dist) { }

    Vec2 n() const { return _normal; }

    Vec2 t() const { return _tangent; }

    Vec2 r1() const { return _r1; }

    Vec2 r2() const { return _r2; }

    float depth() const { return _dist; }

    void swap();

private:
    Vec2 _normal;
    Vec2 _tangent;
    Vec2 _r1;
    Vec2 _r2;
    float _dist;
};

#endif //NATIVE_ACTIVITY_COLLISION_H
