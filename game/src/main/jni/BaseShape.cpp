#include "BaseShape.h"
#include "ShapeTypes.h"

BaseShape::BaseShape() : realChildCount(0), parent(NULL), angle(0.f), aabb(NULL), extendedAABB(NULL) {
}

void BaseShape::move(const Vec2 &coords) {
    if (!parent) {
        center += coords;
    }
//    if (aabb) {
//        aabb->move(coords);
//    }
    for (int i = 0; i < realChildCount; i++) {
        children[i]->move(coords);
    }
}

Vec2 BaseShape::getCenter() const {
    if (parent != NULL) {
        return parent->getCenter();
    }
    return center;
}

BaseShape *BaseShape::getChildren(int i) {
    if (realChildCount == 0) {
        return this;
    }
    return children[i];
}

void BaseShape::rotate(const float angle) {
    for (int i = 0; i < realChildCount; i++) {
        getChildren(i)->rotate(angle);
    }
    innerRotate(angle);
}

void BaseShape::innerRotate(float angle) {
    this->angle += angle;
}

float BaseShape::getAngel() const {
    if (parent != NULL) {
        return parent->getAngel();
    }
    return angle;
}

int BaseShape::getSimpleShapesCount() const {
    return realChildCount == 0 ? 1 : realChildCount;
}

void BaseShape::calculateInnerAABB() {

}

BaseShape::~BaseShape() {
    if (aabb) {
        delete aabb;
    }
}

void BaseShape::calculateExtendAABB(const Vec2 &moveVec) {
    if (aabb) {
        if (!extendedAABB) {
            extendedAABB = new AABB(aabb, moveVec);
        }
        extendedAABB->set(aabb, moveVec);
    }
    for (int i = 0; i < realChildCount; i++) {
        children[i]->calculateExtendAABB(moveVec);
    }
}

AABB *BaseShape::getExtendedAABB() {
    return extendedAABB;
}

void BaseShape::setAngle(float angle) {
    this->angle = angle;
}

void BaseShape::calculateAABB() {
    for (int i = 0; i < realChildCount; i++) {
        children[i]->calculateAABB();
    }
    calculateInnerAABB();
}

void BaseShape::setCenter(const Vec2 &center) {
    this->center = center;
}

unsigned int BaseShape::type() const {
    return ShapeTypes::BASE_SHAPE;
}

AABB *BaseShape::getAABB() {
    return aabb;
}
