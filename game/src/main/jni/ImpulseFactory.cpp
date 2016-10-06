#include "ImpulseFactory.h"
#include "Constants.h"

float ImpulseFactory::createImpulse(const PhysicsObject *o1, const PhysicsObject *o2,
                                    const Collision *c, bool isTangent) {

    Vec2 n = isTangent ? c->t() : c->n();

    Vec2 v1 = o1->getVel() + (Vec2::cross(o1->getAngleVel(), c->r1()));
    Vec2 v2 = o2->getVel() + (Vec2::cross(o2->getAngleVel(), c->r2()));

    float vrn = Vec2::dot(v2 - v1, n);
    if (!isTangent) vrn -= 0.1 * fmax(c->depth() - 0.01f, 0.0f) / DT;

    return -1.f * vrn / (o1->getInvM() + o2->getInvM() +
                         Vec2::dot(o1->getInvI() * Vec2::cross(Vec2::cross(c->r1(), n), c->r1()) +
                                   o2->getInvI() * Vec2::cross(Vec2::cross(c->r2(), n), c->r2()), n));
}

float ImpulseFactory::createImpulse(const PhysicsObject *o1, const PhysicsObject *o2,
                                    const Collision *c) {
    ImpulseFactory::createImpulse(o1, o2, c, false);
}
