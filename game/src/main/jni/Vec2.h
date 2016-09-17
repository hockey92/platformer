#ifndef TEAPOT_VEC2_H
#define TEAPOT_VEC2_H

#include <math.h>

class Vec2 {

public:
    Vec2();

    Vec2(float x, float y);

    Vec2(const Vec2 &v);

    Vec2 &operator+=(const Vec2 &v);

    Vec2 &operator-=(const Vec2 &v);

    Vec2 &operator*=(const float &c);

    float x() const { return values[0]; }

    float y() const { return values[1]; }

    Vec2 &operator=(const Vec2 &v);

    float get(int i) const {
        return values[i];
    }

    float len() const {
        return sqrtf(values[0] * values[0] + values[1] * values[1]);
    }

    float len2() const {
        return values[0] * values[0] + values[1] * values[1];
    }

    Vec2 rotate(float angle) const;

    static float dot(const Vec2 &v1, const Vec2 &v2) {
        return v1.values[0] * v2.values[0] + v1.values[1] * v2.values[1];
    }

    static float cross(const Vec2 &v1, const Vec2 &v2) {
        return v1.values[0] * v2.values[1] - v1.values[1] * v2.values[0];
    }

    static Vec2 cross(const Vec2 &v1, float v2) {
        return Vec2(v1.values[1] * v2, -v1.values[0] * v2);
    }

    static Vec2 cross(float v1, const Vec2 &v2) {
        return Vec2(-v1 * v2.values[1], v1 * v2.values[0]);
    }

private:
    float values[2];
};

Vec2 operator+(Vec2 v1, const Vec2 &v2);

Vec2 operator-(Vec2 v1, const Vec2 &v2);

Vec2 operator*(Vec2 v, const float &c);

Vec2 operator*(const float &c, Vec2 v);

#endif //TEAPOT_VEC2_H
