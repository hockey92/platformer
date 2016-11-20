#include "Collision.h"

void Collision::swap() {
    _normal *= -1;
    Vec2 c = _r1;
    _r1 = _r2;
    _r2 = c;
}
