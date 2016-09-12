#ifndef NATIVE_ACTIVITY_LINE_H
#define NATIVE_ACTIVITY_LINE_H

#include "Vec2.h"

class LineException {
};

class Line {
public:
    Line();

    Line(const Vec2 &p1, const Vec2 &p2);

    float getValue(const Vec2 &p) const;

    Vec2 getNormal() const;

    float getDistToPoint(const Vec2 &p) const;

    static float getDet(const Line &l1, const Line &l2);

    static Vec2 getMutualPoint(const Line &l1, const Line &l2);

    void calculate(const Vec2 &p1, const Vec2 &p2);

private:
    //line coefficients
    float c[3];
    float invSqrt;
};

#endif //NATIVE_ACTIVITY_LINE_H
