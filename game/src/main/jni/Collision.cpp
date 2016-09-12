#include "Collision.h"

void Collision::swap() {
    normal *= -1;
    Vec2 c = r1;
    r1 = r2;
    r2 = c;
}
