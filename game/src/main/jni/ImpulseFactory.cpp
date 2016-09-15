#include "ImpulseFactory.h"
#include "Constants.h"

float ImpulseFactory::createImpulse(const PhysicsObject *o1,
                                    const PhysicsObject *o2,
                                    const Collision *c) {

    Vec2 v1 = o1->getVel() + (Vec2::cross(o1->getAngleVel(), c->r1()));
    Vec2 v2 = o2->getVel() + (Vec2::cross(o2->getAngleVel(), c->r2()));

    float vrn = Vec2::dot(v2 - v1, c->n());
    vrn -= 0.2f * fmax(c->depth() - 0.01f, 0.0f) / DT;
    return -1.f * vrn / (o1->getInvM() + o2->getInvM() +
                         Vec2::dot(o1->getInvI() * Vec2::cross(Vec2::cross(c->r1(), c->n()), c->r1()) +
                                   o2->getInvI() * Vec2::cross(Vec2::cross(c->r2(), c->n()), c->r2()), c->n()));
}
