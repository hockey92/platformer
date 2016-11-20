#ifndef NATIVE_ACTIVITY_PHYSICSOBJECT_H
#define NATIVE_ACTIVITY_PHYSICSOBJECT_H

#include "Vec2.h"
#include "BaseShape.h"
#include "Mutex.h"
#include "Constants.h"

class PhysicsObject {

public:
    PhysicsObject(BaseShape *shape, float invM, float invI);

    PhysicsObject *move(const Vec2 &dPos);

    virtual ~PhysicsObject();

    virtual void update() { }

    virtual void updatePos();

    void applyForce();

    Vec2 getVel() const { return vel; }

    float getAngleVel() const { return angleVel; }

    void setVel(const Vec2 &vel) { this->vel = vel; }

    void setAcceleration(const Vec2 &acceleration) {
        this->acceleration = acceleration;
    }

    void setVelThreshold(const Vec2& velThreshold) {
        this->velThreshold = velThreshold;
    }

    void setAngleVel(float angleVel) {
        this->angleVel = angleVel;
    }

    float getInvM() const {
        return invM;
    }

    float getInvI() const {
        return invI;
    }

    void applyImpulse(const Vec2 &dVel, float dAngleVel) {
        if (invM > 0) {
            vel += dVel;
            angleVel += dAngleVel;
        }
    }

    BaseShape *getShape() const { return shape; }

    bool isActive();

    bool isDeleted() { return deleted; }

    void setDeleted(bool deleted) { this->deleted = deleted; }

    void setActive(bool active) { this->active = active; }

    void calculateExtendedAABB();

    bool isVisible() { return visible && !deleted; }

    void setVisible(bool visible) { this->visible = visible; }

    unsigned int getId() const { return id; }

protected:
    PhysicsObject();

    void setShape(BaseShape *shape) { this->shape = shape; }

    void setInvM(float invM) { this->invM = invM; }

    void setInvI(float invI) { this->invI = invI; }

private:
    Vec2 vel;
    Vec2 acceleration;
    Vec2 velThreshold;
    float angleVel;
    BaseShape *shape;
    float invM;
    float invI;
    bool active;
    bool deleted;
    bool visible;

    unsigned int id;

    static Mutex idMutex;
    static unsigned int idCounter;
};

#endif //NATIVE_ACTIVITY_PHYSICSOBJECT_H
