#include "CollisionInfo.h"
#include "IdUtils.h"
#include <vector>
#include "common.h"
#include "PhysicsObject.h"
#include "Collision.h"
#include "Constraint.h"

CollisionInfo::CollisionInfo(PhysicsObject *o1, PhysicsObject *o2) {
    this->_o1 = o1;
    this->_o2 = o2;

    swapIfNeeded();

    _size = 0;
    _maxSize = 0;

    _newCollisionInfo = true;
}

void CollisionInfo::swapIfNeeded() {
    _swapped = false;
    if (_o1->getId() > _o2->getId()) {
        PhysicsObject *temp = _o1;
        _o1 = _o2;
        _o2 = temp;
        _swapped = true;
    }
}

unsigned int CollisionInfo::getId() const {
    return IdUtils::createKey(_o1->getId(), _o2->getId());
}

bool CollisionInfo::isCalculateNewCollision() {

    if (_newCollisionInfo) {
        return true;
    }

    float d = 0.001f, dAngle = 0.001f;

    Vec2 currDiff = _o1->getShape()->getCenter() - _o2->getShape()->getCenter();
    if (fabs(_diff.x() - currDiff.x()) > d || fabs(_diff.y() - currDiff.y()) > d) {
        return true;
    } else if (fabs(_angle1 - _o1->getShape()->getAngel()) > dAngle ||
               fabs(_angle2 - _o2->getShape()->getAngel()) > dAngle) {
        return true;
    }
    return false;
}

void CollisionInfo::calculateDiff() {

    _newCollisionInfo = false;

    _diff = _o1->getShape()->getCenter() - _o2->getShape()->getCenter();
    _angle1 = _o1->getShape()->getAngel();
    _angle2 = _o2->getShape()->getAngel();
    _size = 0;
}

bool operator<(const CollisionInfo &x, const CollisionInfo &y) {
    return x.getId() < y.getId();
}

void CollisionInfo::addConstraint(Collision *c) {
    if (_size == _maxSize) {
        _constraints[_size] = _swapped ? new Constraint(_o2, _o1, c) : new Constraint(_o1, _o2, c);
        _maxSize++;
    } else {
        if (_swapped) {
            _constraints[_size]->set(_o2, _o1, c);
        } else {
            _constraints[_size]->set(_o1, _o2, c);
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
        _constraints[i]->fix();
    }
}

void CollisionInfo::clean() {
    _size = 0;
}

void CollisionInfo::addConstraints(const std::vector<Collision *> &collisions) {
    if (_size != collisions.size()) {
        clean();
        for (int i = 0; i < collisions.size(); i++) {
            addConstraint(collisions[i]);
        }
    } else {
        for (int i = 0; i < _size; i++) {
            _constraints[i]->setCollision(collisions[i]);
        }
    }
}

void CollisionInfo::applyWarmStarting() {
    for (int i = 0; i < _size; i++) {
        _constraints[i]->applyWarmStarting();
    }
}
