#ifndef NATIVE_ACTIVITY_IMPULSEFACTORY_H
#define NATIVE_ACTIVITY_IMPULSEFACTORY_H

#include "Collision.h"
#include "PhysicsObject.h"

class ImpulseFactory {
public:
    static float createImpulse(const PhysicsObject *o1, const PhysicsObject *o2,
                                  const Collision *c, bool isTangent);

    static float createImpulse(const PhysicsObject *o1, const PhysicsObject *o2,
                               const Collision *c);
};

#endif //NATIVE_ACTIVITY_IMPULSEFACTORY_H
