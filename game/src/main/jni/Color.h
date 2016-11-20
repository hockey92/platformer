#ifndef NATIVE_ACTIVITY_COLOR_H
#define NATIVE_ACTIVITY_COLOR_H

#include <math.h>

class Color {
public:
    Color() : _r(0), _g(0), _b(0), _a(0) { }

    Color(float r, float g, float b, float a) : _r(r), _g(g), _b(b), _a(a) { }

    float r() const { return _r; }

    float g() const { return _g; }

    float b() const { return _b; }

    float a() const { return _a; }

private:
    float _r;
    float _g;
    float _b;
    float _a;
};

#endif //NATIVE_ACTIVITY_COLOR_H
