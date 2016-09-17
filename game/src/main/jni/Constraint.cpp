#include "Constraint.h"
#include "ImpulseFactory.h"

Constraint::Constraint(PhysicsObject *o1, PhysicsObject *o2, Collision *c) {
    set(o1, o2, c);
}

void Constraint::fix() {
    float j = ImpulseFactory::createImpulse(o1, o2, c);
    float oldImpulse = normalTotalImpulse;
    normalTotalImpulse = clamp(oldImpulse + j);
    j = normalTotalImpulse - oldImpulse;
    o1->applyImpulse(-j * o1->getInvM() * c->n(),
                     -j * o1->getInvI() * Vec2::cross(c->r1(), c->n()));
    o2->applyImpulse(j * o2->getInvM() * c->n(),
                     j * o2->getInvI() * Vec2::cross(c->r2(), c->n()));

    j = ImpulseFactory::createImpulse(o1, o2, c, true);
    oldImpulse = tangentTotalImpulse;
    tangentTotalImpulse = clamp(oldImpulse + j, -0.4f * normalTotalImpulse, 0.4f * normalTotalImpulse);
    j = tangentTotalImpulse - oldImpulse;
    o1->applyImpulse(-j * o1->getInvM() * c->t(),
                     -j * o1->getInvI() * Vec2::cross(c->r1(), c->t()));
    o2->applyImpulse(j * o2->getInvM() * c->t(),
                     j * o2->getInvI() * Vec2::cross(c->r2(), c->t()));
}

float Constraint::clamp(float impulse) {
    if (impulse < 0) {
        return 0;
    }
    return impulse;
}

void Constraint::set(PhysicsObject *o1, PhysicsObject *o2, Collision *c) {
    this->c = c;

    this->o1 = o1;
    this->o2 = o2;

    normalTotalImpulse = 0;
    tangentTotalImpulse = 0;
}

void Constraint::reset() {
    normalTotalImpulse = 0;
}

Constraint::~Constraint() {
    delete c;
}

float Constraint::clamp(float impulse, float min, float max) {
    if (impulse < min) {
        return min;
    }
    if (impulse > max) {
        return max;
    }
    return impulse;
}
