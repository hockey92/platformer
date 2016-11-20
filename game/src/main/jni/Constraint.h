#ifndef NATIVE_ACTIVITY_CONSTRAINT_H
#define NATIVE_ACTIVITY_CONSTRAINT_H

#include "PhysicsObject.h"
#include "Collision.h"

class Constraint {
public:
    Constraint(PhysicsObject *o1, PhysicsObject *o2, Collision *c);

    virtual ~Constraint();

    void fix();

    void set(PhysicsObject *o1, PhysicsObject *o2, Collision *c);

    void reset();

    void setCollision(Collision* newCollision);

    void applyWarmStarting();

    void deleteCollision();

private:
    PhysicsObject *o1;
    PhysicsObject *o2;
    Collision *c;
    float normalTotalImpulse;
    float tangentTotalImpulse;

    float clamp(float impulse);
    float clamp(float impulse, float min, float max);
};

#endif //NATIVE_ACTIVITY_CONSTRAINT_H
