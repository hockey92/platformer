#include "SegmentShape.h"

SegmentShape::SegmentShape(Vec2 p1, Vec2 p2) : BaseShape() {
    init(p1, p2);
}

SegmentShape::SegmentShape(BaseShape *parent, Vec2 p1, Vec2 p2) : BaseShape() {
    init(p1, p2);
    this->parent = parent;
}

void SegmentShape::init(Vec2 p1, Vec2 p2) {
    points[0] = initPoints[0] = p1;
    points[1] = initPoints[1] = p2;
    calculateInnerAABB();
}

Vec2 SegmentShape::get(int i) const {
    return getCenter() + points[i];
}

void SegmentShape::innerRotate(float angle) {
    this->angle += angle;
    points[0] = initPoints[0].rotate(this->angle);
    points[1] = initPoints[1].rotate(this->angle);
}

void SegmentShape::calculateInnerAABB() {
    Vec2 points[2] = {this->points[0] + getCenter(), this->points[1] + getCenter()};
    float right = fmaxf(points[0].x(), points[1].x());
    float left = fminf(points[0].x(), points[1].x());
    float up = fmaxf(points[0].y(), points[1].y());
    float down = fminf(points[0].y(), points[1].y());

    if (aabb == NULL) {
        aabb = new AABB(left, down, right, up);
    } else {
        aabb->set(left, down, right, up);
    }
}

Vec2 SegmentShape::getPoint(int i) const {
    return points[i];
}

unsigned int SegmentShape::type() const {
    return ShapeTypes::SEGMENT;
}
