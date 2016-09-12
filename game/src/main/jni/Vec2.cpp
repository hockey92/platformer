#include "Vec2.h"

Vec2::Vec2(float x, float y) {
    values[0] = x;
    values[1] = y;
}

Vec2::Vec2(const Vec2 &v) {
    values[0] = v.values[0];
    values[1] = v.values[1];
}

Vec2 &Vec2::operator+=(const Vec2 &v) {
    values[0] += v.values[0];
    values[1] += v.values[1];
    return *this;
}

Vec2 operator+(Vec2 v1, const Vec2 &v2) {
    return v1 += v2;
}

Vec2 &Vec2::operator-=(const Vec2 &v) {
    values[0] -= v.values[0];
    values[1] -= v.values[1];
    return *this;
}

Vec2 operator-(Vec2 v1, const Vec2 &v2) {
    return v1 -= v2;
}

Vec2 &Vec2::operator*=(const float &c) {
    values[0] *= c;
    values[1] *= c;
    return *this;
}

Vec2 operator*(Vec2 v, const float &c) {
    return v *= c;
}

Vec2 operator*(const float &c, Vec2 v) {
    return v *= c;
}

Vec2::Vec2() {
    values[0] = 0;
    values[1] = 0;
}

Vec2 &Vec2::operator=(const Vec2 &v) {
    values[0] = v.values[0];
    values[1] = v.values[1];
    return *this;
}

Vec2 Vec2::rotate(float angle) const {
    return Vec2(
            cosf(angle) * values[0] - sinf(angle) * values[1],
            sinf(angle) * values[0] + cosf(angle) * values[1]
    );
}
