#ifndef NATIVE_ACTIVITY_CONSTRAINT_H
#define NATIVE_ACTIVITY_CONSTRAINT_H

#include "PhysicsObject.h"
#include "Collision.h"

class Constraint {
public:
    Constraint(PhysicsObject *o1, PhysicsObject *o2, Collision *c);

    virtual ~Constraint();

    bool fix();

    void set(PhysicsObject *o1, PhysicsObject *o2, Collision *c);

    void reset();

private:
    PhysicsObject *o1;
    PhysicsObject *o2;
    Collision *c;
    float totalImpulse;

    float clamp(float impulse);
};

#endif //NATIVE_ACTIVITY_CONSTRAINT_H
