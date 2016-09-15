#include "Constraint.h"
#include "ImpulseFactory.h"

Constraint::Constraint(PhysicsObject *o1, PhysicsObject *o2, Collision *c) {
    set(o1, o2, c);
}

bool Constraint::fix() {
    float j = ImpulseFactory::createImpulse(o1, o2, c);
    float oldImpulse = totalImpulse;
    totalImpulse = clamp(oldImpulse + j);
    j = totalImpulse - oldImpulse;
    o1->applyImpulse(-j * o1->getInvM() * c->n(), -j * o1->getInvI() * Vec2::cross(c->r1(), c->n()));
    o2->applyImpulse(j * o2->getInvM() * c->n(), j * o2->getInvI() * Vec2::cross(c->r2(), c->n()));

//    if (fabsf(j) > 1.0f) {
//        LOGE("impulse %f", fabsf(j));
//    }

    return fabsf(j) > 1.0f;
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

    totalImpulse = 0;
}

void Constraint::reset() {
    totalImpulse = 0;
}

Constraint::~Constraint() {
    delete c;
}
