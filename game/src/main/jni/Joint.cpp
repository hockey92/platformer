//
// Created by qwerty on 02.10.16.
//

#include "Joint.h"
#include "Constants.h"

void Joint::innerUpdate() {
    BaseShape* child = realChildCount > 0 ? getChildren(0) : NULL;

    if (parent == NULL || child == NULL) {
        return;
    }

    float angle1 = parent->getAngel() + parentPolarCoords.angle;
    Vec2 vec1 = Vec2(cos(angle1) * parentPolarCoords.r, sin(angle1) * parentPolarCoords.r);
    float angle2 = angle1 + angleBetweenParentAndChild;
    Vec2 vec2 = Vec2(cos(angle2) * childPolarCoords.r, sin(angle2) * childPolarCoords.r);
    child->setCenter(parent->getCenter() + vec1 - vec2);

    child->setAngle(angle2 - PI);
    child->rotate(0);
}

Joint::Joint(PolarCoords parentPolarCoords,
             PolarCoords childPolarCoords) {
    this->parentPolarCoords = parentPolarCoords;
    this->childPolarCoords = childPolarCoords;
}
