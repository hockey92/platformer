#include "BasePhysicsService.h"
#include "CollisionFactory.h"
#include "common.h"
#include "IdUtils.h"

BasePhysicsService::BasePhysicsService() : status(STOPPED) {
    pthread_mutex_init(&mutex, NULL);

    Vec2 vertices1[] = {Vec2(19.f, 1.f),
                        Vec2(-19.f, 1.f),
                        Vec2(-19.f, -1.f),
                        Vec2(19.f, -1.f)};
    physicsObjects.push_back(new PhysicsObject(new PolygonShape(vertices1, 4), 0));
    physicsObjects.back()->getShape()->move(Vec2(0, -10.f));
//    physicsObjects.back()->getShape()->rotate(0.2f);

    Vec2 vertices2[] = {Vec2(2.f, 2.f),
                        Vec2(-2.f, 2.f),
                        Vec2(-2.f, -2.f),
                        Vec2(2.f, -2.f)};

    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) {
            physicsObjects.push_back(new PhysicsObject(new PolygonShape(vertices2, 4), 1.f));
            physicsObjects.back()->getShape()->move(
                    Vec2(-5 * (i / 2) - (i % 2) * 2.5f + j * 5, -i * 5 + 30));
        }
    }

    physicsObjects.pop_back();
    physicsObjects.pop_back();

    for (int i = 0; i < physicsObjects.size(); i++) {
        physicsObjects[i]->getShape()->calculateAABB();
    }

    for (int i = 0; i < 10000000; i++) {
        collisionInfos[i] = NULL;
    }
}

void BasePhysicsService::nextFrame() {

//    double beforeTime = now();

    std::vector<CollisionInfo *> collisionInfos1;

    if (status != PROCESSING) {
        return;
    }

    doActionBefore();

    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->update();
        po->applyGravity();
//        po->calculateExtendedAABB();
    }

    int newCollisionsCount = 0;

    double updateTime = now();
    int skiped = 0;
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

            collisionInfo->calculateDiff();
//
//            if (!collisionInfo->isCalculateNewCollision()) {
//                if (!collisionInfo->isEmpty()) {
//                    collisionInfos1.push_back(collisionInfo);
//                }
//            } else {
//                collisionInfo->calculateDiff();
            for (int k = 0; k < po1->getShape()->getSimpleShapesCount(); k++) {
                for (int l = 0; l < po2->getShape()->getSimpleShapesCount(); l++) {
                    BaseShape *shape1 = po1->getShape()->getChildren(k);
                    BaseShape *shape2 = po2->getShape()->getChildren(l);
                    if (!AABB::isIntersect(shape1->getAABB(), shape2->getAABB())) {
                        skiped++;
                        continue;
                    }
                    newCollisionsCount++;
                    std::vector<Collision *> c = CollisionFactory::createCollision(
                            (PolygonShape *) shape1, (PolygonShape *) shape2);
                    if (!c.empty()) {
                        for (int collisionNumber = 0;
                             collisionNumber < c.size(); collisionNumber++) {
                            collisionInfo->addConstraint(c[collisionNumber]);
                        }
                    }
                }
            }
            if (!collisionInfo->isEmpty()) {
                collisionInfos1.push_back(collisionInfo);
            }
//            }
        }
    }
    LOGE("updateTime %f", now() - updateTime);

    LOGE("new collisions count %d", newCollisionsCount);

    LOGE("skiped %d", skiped);

    for (int iteration = 0; iteration < 10; iteration++) {
        for (int i = 0; i < collisionInfos1.size(); i++) {
            collisionInfos1[i]->fix();
        }
    }

    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->updatePos();
    }

    doActionAfter();
}

int BasePhysicsService::getStatus() {
    return status;
}

void BasePhysicsService::setStatus(int status) {
    this->status = status;
}

BasePhysicsService::~BasePhysicsService() {
    for (int i = 0; i < physicsObjects.size(); i++) {
        delete physicsObjects[i];
    }
}

void BasePhysicsService::innerRun() {
//    double time = now();
//    while (!isStop) {
//        double currentTime = now();
//        LOGE("timeDiff %f", currentTime - time);
//        time = currentTime;
//        double timeBefore = now();
//        nextFrame();
//        double timeAfter = now();
//
//        int delay = 16 - (int) (timeAfter - timeBefore);
//        delay = delay < 2 ? 2 : delay;
//        usleep((unsigned int) delay * 1000);
//    }
}

void BasePhysicsService::addPhysicsObjects(PhysicsObject *physicsObject) {
    physicsObjects.push_back(physicsObject);
}
