#include "Constants.h"
#include "PhysicsObject.h"

unsigned int PhysicsObject::idCounter = 0;

Mutex PhysicsObject::idMutex;

PhysicsObject::PhysicsObject(BaseShape *shape, float invM, float invI)
        : angleVel(0), shape(shape), invM(invM), invI(invI),
          active(true), deleted(false),
          visible(true) {
    idMutex.lock();
    id = idCounter++;
    idMutex.unlock();
}

PhysicsObject::PhysicsObject() : angleVel(0), shape(NULL), invM(0),
                                 active(true), deleted(false), visible(true) {
    idMutex.lock();
    id = idCounter++;
    idMutex.unlock();
}

void PhysicsObject::updatePos() {
    if (shape) {
        shape->rotate(angleVel * DT);
        shape->move(vel * DT);
        shape->calculateAABB();
    }
}

void PhysicsObject::applyForce() {
    if (invM > 0.f) {
        vel += Vec2(0.0f, -9.8f) * DT;
        vel += acceleration * DT;
        vel.clamp(Vec2(7, -1));
    }
}

PhysicsObject::~PhysicsObject() {
    if (shape) {
        delete shape;
    }
}

void PhysicsObject::calculateExtendedAABB() {
    shape->calculateExtendAABB(vel * DT);
}

bool PhysicsObject::isActive() {
    return active && !deleted;
}

PhysicsObject *PhysicsObject::move(const Vec2 &dPos) {
    if (shape) {
        shape->move(dPos);
    }
    return this;
}
