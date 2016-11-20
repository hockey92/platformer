#include "PhysicsService.h"
#include "CollisionFactory.h"
#include "IdUtils.h"
#include "TimeUtils.h"
#include "common.h"

PhysicsService::PhysicsService() : status(STOPPED) {
    for (int i = 0; i < 10000000; i++) {
        collisionInfos[i] = NULL;
    }
}

void PhysicsService::nextFrame() {
    double time = TimeUtils::now();
    if (status != PROCESSING) {
        return;
    }

    std::vector<CollisionInfo *> collisionsToFix;

    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->update();
        po->applyForce();
    }

    double collisionTime = TimeUtils::now();
    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po1 = physicsObjects[i];
        if (!po1->isActive()) {
            continue;
        }
        for (int j = i + 1; j < physicsObjects.size(); j++) {
            PhysicsObject *po2 = physicsObjects[j];
            if (!po2->isActive()) {
                continue;
            }
            int collisionId = IdUtils::createKey(po1->getId(), po2->getId());

            CollisionInfo *collisionInfo = collisionInfos[collisionId];
            if (collisionInfo == NULL) {
                collisionInfo = collisionInfos[collisionId] = new CollisionInfo(po1, po2);
            }

            for (int k = 0; k < po1->getShape()->getSimpleShapesCount(); k++) {
                for (int l = 0; l < po2->getShape()->getSimpleShapesCount(); l++) {
                    BaseShape *shape1 = po1->getShape()->getChildren(k);
                    BaseShape *shape2 = po2->getShape()->getChildren(l);
                    if (!AABB::isIntersect(shape1->getAABB(), shape2->getAABB())) {
                        collisionInfo->clean();
                        continue;
                    }

                    std::vector<Collision *> collisions = CollisionFactory::createCollision(
                            (PolygonShape *) shape1,
                            (PolygonShape *) shape2
                    );

                    if (!collisions.empty()) {
                        collisionInfo->addConstraints(collisions);
                    } else {
                        collisionInfo->clean();
                    }
                }
            }
            if (!collisionInfo->isEmpty()) {
                collisionsToFix.push_back(collisionInfo);
            }
        }
    }
//    LOGE("collision time ndk %f", TimeUtils::now() - collisionTime);

    for (int i = 0; i < collisionsToFix.size(); i++) {
        collisionsToFix[i]->applyWarmStarting();
    }

    for (int iteration = 0; iteration < 10; iteration++) {
        for (int i = 0; i < collisionsToFix.size(); i++) {
            collisionsToFix[i]->fix();
        }
    }

    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->updatePos();
    }
//    LOGE("time ndk %f", TimeUtils::now() - time);
}

int PhysicsService::getStatus() {
    return status;
}

void PhysicsService::setStatus(int status) {
    this->status = status;
}

PhysicsService::~PhysicsService() {
    for (int i = 0; i < physicsObjects.size(); i++) {
        delete physicsObjects[i];
    }
}

void PhysicsService::addPhysicsObject(PhysicsObject *physicsObject) {
    physicsObject->getShape()->calculateAABB();
    physicsObjects.push_back(physicsObject);
}
