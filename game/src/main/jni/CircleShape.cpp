#include "CircleShape.h"
#include "ShapeTypes.h"

CircleShape::CircleShape(float r) : BaseShape() {
    this->r = r;
    calculateInnerAABB();
}

float CircleShape::getR() const {
    return r;
}

unsigned int CircleShape::type() const {
    return ShapeTypes::CIRCLE;
}

void CircleShape::calculateInnerAABB() {
    float x = getCenter().x(), y = getCenter().y();
    float right = x + r;
    float up = y + r;
    float left = x - r;
    float down = y - r;

    if (aabb == NULL) {
        aabb = new AABB(left, down, right, up);
    } else {
        aabb->set(left, down, right, up);
    }
}
