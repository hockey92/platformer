#ifndef NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
#define NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "Constraint.h"
#include "IThread.h"
#include "Map.h"
#include "CollisionInfo.h"
#include "CollisionInfo.h"

enum {
    STOPPED, PROCESSING, PAUSED
};

class PhysicsService {
public:
    PhysicsService();

    virtual ~PhysicsService();

    void nextFrame();

    int getStatus();

    void setStatus(int status);

    void addPhysicsObject(PhysicsObject *physicsObject);

    void draw(float* mvp);

private:
    int status;
    CollisionInfo *collisionInfos[10000000];
    std::vector<PhysicsObject *> physicsObjects;
};

#endif //NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
