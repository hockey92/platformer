#include "ImpulseFactory.h"
#include "Constants.h"

float ImpulseFactory::createImpulse(const PhysicsObject *o1,
                                    const PhysicsObject *o2,
                                    const Collision *c) {

    Vec2 v1 = o1->getVel() + (Vec2::cross(o1->getAngleVel(), c->getR1()));
    Vec2 v2 = o2->getVel() + (Vec2::cross(o2->getAngleVel(), c->getR2()));

    float vrn = Vec2::dot(v2 - v1, c->getNormal());
    vrn -=  c->getDist() / DT;
    return -1.f * vrn / (o1->getInvM() + o2->getInvM());
}
