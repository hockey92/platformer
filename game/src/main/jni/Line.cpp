#include <math.h>
#include "Line.h"
#include "common.h"

Line::Line(const Vec2 &p1, const Vec2 &p2) {
    calculate(p1, p2);
}

Line::Line() {

}

Vec2 Line::getMutualPoint(const Line &l1, const Line &l2) {
    float d = getDet(l1, l2);
    ASSERT(d != 0)
    float d1 = -l1.c[2] * l2.c[1] + l1.c[1] * l2.c[2];
    float d2 = -l1.c[0] * l2.c[2] + l1.c[2] * l2.c[0];
    return Vec2(d1 / d, d2 / d);
}

float Line::getValue(const Vec2 &p) const {
    return c[0] * p.x() + c[1] * p.y() + c[2];
}

Vec2 Line::getNormal() const {
    return Vec2(c[0] * invSqrt, c[1] * invSqrt);
}

float Line::getDistToPoint(const Vec2 &p) const {
    return getValue(p) * invSqrt;
}

float Line::getDet(const Line &l1, const Line &l2) {
    return l1.c[0] * l2.c[1] - l1.c[1] * l2.c[0];
}

void Line::calculate(const Vec2 &p1, const Vec2 &p2) {
    c[0] = p1.y() - p2.y();
    c[1] = p2.x() - p1.x();
    c[2] = p1.x() * p2.y() - p1.y() * p2.x();
    invSqrt = 1.f / sqrtf(c[0] * c[0] + c[1] * c[1]);
}
