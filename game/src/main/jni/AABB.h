#ifndef NATIVE_ACTIVITY_AABB_H
#define NATIVE_ACTIVITY_AABB_H

#include "Vec2.h"

class AABB {
public:
    AABB() { }

    AABB(float left, float down, float right, float up);

    AABB(const AABB *aabb, const Vec2 &moveVec);

    AABB(const AABB &aabb, const Vec2 &moveVec);

    void set(const AABB *aabb, const Vec2 &moveVec);

    void set(float left, float down, float right, float up);

    static bool isIntersect(const AABB *a, const AABB *b);

    void move(const Vec2 &d);

    bool isPointBelong(const Vec2 &point);

    void getCoords(float& left, float& right, float& up, float& down) const;

    Vec2 getCenter() const;

private:
    float left;
    float right;
    float up;
    float down;
};

#endif //NATIVE_ACTIVITY_AABB_H
