#include "Vec2.h"
#include <sstream>

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

std::string Vec2::floatToStr(float value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

void Vec2::clamp(const Vec2 &v) {
    for (int i = 0; i < 2; i++) {
        if (v.values[i] < 0) {
            continue;
        }
        if (values[i] > v.values[i]) {
            values[i] = v.values[i];
        } else if (values[i] < -v.values[i]) {
            values[i] = -v.values[i];
        }
    }
}
