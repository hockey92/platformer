#include "CollisionInfo.h"
#include "IdUtils.h"
#include "common.h"
#include "PhysicsObject.h"
#include "Collision.h"
#include "Constraint.h"

CollisionInfo::CollisionInfo(PhysicsObject *o1, PhysicsObject *o2) {
    this->o1 = o1;
    this->o2 = o2;

    swapIfNeeded();

    _size = 0;
    _maxSize = 0;

    newCollisionInfo = true;
}

void CollisionInfo::swapIfNeeded() {
    swapped = false;
    if (o1->getId() > o2->getId()) {
        PhysicsObject *temp = o1;
        o1 = o2;
        o2 = temp;
        swapped = true;
    }
}

unsigned int CollisionInfo::getId() const {
    return IdUtils::createKey(o1->getId(), o2->getId());
}

bool CollisionInfo::isCalculateNewCollision() {

    if (newCollisionInfo) {
        return true;
    }

//    return true;

    float d = 0.0001f, dAngle = 0.0001f;

    Vec2 currDiff = o1->getShape()->getCenter() - o2->getShape()->getCenter();
    if (fabs(diff.x() - currDiff.x()) > d || fabs(diff.y() - currDiff.y()) > d) {
        return true;
    } else if (fabs(angle1 - o1->getShape()->getAngel()) > dAngle ||
               fabs(angle2 - o2->getShape()->getAngel()) > dAngle) {
        return true;
    }
    return false;
}

void CollisionInfo::calculateDiff() {

    newCollisionInfo = false;

    diff = o1->getShape()->getCenter() - o2->getShape()->getCenter();
    angle1 = o1->getShape()->getAngel();
    angle2 = o2->getShape()->getAngel();
    _size = 0;
}

bool operator<(const CollisionInfo &x, const CollisionInfo &y) {
    return x.getId() < y.getId();
}

void CollisionInfo::addConstraint(Collision *c) {
    if (_size == _maxSize) {
        constraints[_size] = swapped ? new Constraint(o2, o1, c) : new Constraint(o1, o2, c);
        _maxSize++;
    } else {
        if (swapped) {
            constraints[_size]->set(o2, o1, c);
        } else {
            constraints[_size]->set(o1, o2, c);
        }
    }
    _size++;
}

CollisionInfo::~CollisionInfo() {

}

bool CollisionInfo::isEmpty() {
    return _size <= 0;
}

void CollisionInfo::fix() {
    for (int i = 0; i < _size; i++) {
        constraints[i]->fix();
    }
}
