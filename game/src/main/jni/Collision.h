#ifndef NATIVE_ACTIVITY_COLLISION_H
#define NATIVE_ACTIVITY_COLLISION_H

#include <math.h>
#include "Vec2.h"

class Collision {

public:
    Collision(const Vec2 &normal, const Vec2 &r1, const Vec2 &r2, float dist) :
            normal(normal),
            r1(r1),
            r2(r2),
            dist(dist) { }

    Vec2 getNormal() const { return normal; }

    Vec2 getR1() const { return r1; }

    Vec2 getR2() const { return r2; }

    float getDist() const { return dist; }

    void swap();

private:
    Vec2 normal;
    Vec2 r1;
    Vec2 r2;
    float dist;
};

#endif //NATIVE_ACTIVITY_COLLISION_H
