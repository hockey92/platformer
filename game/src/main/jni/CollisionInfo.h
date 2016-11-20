#ifndef INC_100BALLS_COLLISIONINFO_H
#define INC_100BALLS_COLLISIONINFO_H

#include <stl/_vector.h>
#include "PhysicsObject.h"
#include "Constraint.h"

class CollisionInfo {
public:
    CollisionInfo(PhysicsObject *o1, PhysicsObject *o2);

    virtual ~CollisionInfo();

    unsigned int getId() const;

    bool isCalculateNewCollision();

    void calculateDiff();

    void addConstraint(Collision *c);

    void addConstraints(const std::vector<Collision *> &collisions);

    bool isEmpty();

    void fix();

    void clean();

    void applyWarmStarting();

private:
    PhysicsObject *_o1;
    PhysicsObject *_o2;

    void swapIfNeeded();

    Vec2 _diff;
    float _angle1;
    float _angle2;

    int _size;
    int _maxSize;

    bool _swapped;

    bool _newCollisionInfo;

    Constraint *_constraints[1000];

    friend bool operator<(const CollisionInfo &x, const CollisionInfo &y);
};

inline bool operator>(const CollisionInfo &x, const CollisionInfo &y) {
    return y < x;
}

inline bool operator>=(const CollisionInfo &x, const CollisionInfo &y) {
    return !(x < y);
}

inline bool operator<=(const CollisionInfo &x, const CollisionInfo &y) {
    return !(y < x);
}

inline bool operator==(const CollisionInfo &x, const CollisionInfo &y) {
    return !(x < y || y < x);
}

#endif //INC_100BALLS_BASEPHYSICSSERVICEKEY_H
