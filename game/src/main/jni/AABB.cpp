#include "AABB.h"

AABB::AABB(float left, float down, float right, float up) : left(left),
                                                            down(down),
                                                            right(right),
                                                            up(up) { }

AABB::AABB(const AABB *aabb, const Vec2 &moveVec) {
    set(aabb, moveVec);
}

bool AABB::isIntersect(const AABB *a, const AABB *b) {
    if (a == NULL || b == NULL) {
        return true;
    }
    float d = 0.01f;
    return !(a->left - d > b->right || b->left - d > a->right || a->down - d > b->up || b->down - d > a->up);
}

void AABB::set(float left, float down, float right, float up) {
    this->left = left;
    this->down = down;
    this->right = right;
    this->up = up;
}

void AABB::move(const Vec2 &d) {
    right += d.x();
    left += d.x();
    up += d.y();
    down += d.y();
}

void AABB::set(const AABB *aabb, const Vec2 &moveVec) {
    right = fmaxf(aabb->right, aabb->right + moveVec.x());
    left = fminf(aabb->left, aabb->left + moveVec.x());
    up = fmaxf(aabb->up, aabb->up + moveVec.y());
    down = fminf(aabb->down, aabb->down + moveVec.y());
}

bool AABB::isPointBelong(const Vec2 &point) {
    float x = point.x();
    float y = point.y();
    return left <= x && right >= x && down <= y && up >= y;
}

AABB::AABB(const AABB &aabb, const Vec2 &moveVec) {
    set(&aabb, moveVec);
}

void AABB::getCoords(float &left, float &right, float &up, float &down) const {
    left = this->left;
    right = this->right;
    up = this->up;
    down = this->down;
}

Vec2 AABB::getCenter() const {
    return Vec2(left + (right - left) / 2.0f, down + (up - down) / 2.0f);
}
