#include "BasePhysicsService.h"
#include "CollisionFactory.h"
#include "common.h"
#include "IdUtils.h"
#include "RectanglePhysicsObject.h"

BasePhysicsService::BasePhysicsService() : status(STOPPED) {
    pthread_mutex_init(&mutex, NULL);

    physicsObjects.push_back(new RectanglePhysicsObject(100.f, 1.f, 0.f));
    physicsObjects.back()->getShape()->move(Vec2(0, -20.f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 100.f, 0.f));
    physicsObjects.back()->getShape()->move(Vec2(20, 0.f));

/////////////////////////////////
    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(5.0f, -14.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(10.0f, -14.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(15.0f, -14.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(12.f, 1.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(10.0f, -9.0f));
///////////////////////////////////////
    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(5.0f, -3.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(10.0f, -3.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(15.0f, -3.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(12.f, 1.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(10.0f, 2.0f));
//////////////////////////////////////////////////////////
    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(5.0f, 7.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(15.0f, 7.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(1.f, 10.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(10.0f, 7.5f));

    physicsObjects.push_back(new RectanglePhysicsObject(12.f, 1.f, 1.f));
    physicsObjects.back()->getShape()->move(Vec2(10.0f, 13.0f));
//////////////////////////////////////////////////
    physicsObjects.push_back(new RectanglePhysicsObject(2.f, 2.f, 1.0f));
    physicsObjects.back()->getShape()->move(Vec2(-40.0f, 0.0f));
    physicsObjects.back()->setVel(Vec2(40.f, 0.f));


//    for (int i = 1; i <= 6; i++) {
//        for (int j = 0; j < i; j++) {
////            if (i == 5 && j == 2) {
////                continue;
////            }
//            physicsObjects.push_back(new RectanglePhysicsObject(4.f, 4.f, 1.f));
//            physicsObjects.back()->getShape()->move(
//                    Vec2(-5 * (i / 2) - (i % 2) * 2.5f + j * 5 + 20, -i * 5 + 20));
//        }
//    }

//    physicsObjects.pop_back();

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

            for (int k = 0; k < po1->getShape()->getSimpleShapesCount(); k++) {
                for (int l = 0; l < po2->getShape()->getSimpleShapesCount(); l++) {
                    BaseShape *shape1 = po1->getShape()->getChildren(k);
                    BaseShape *shape2 = po2->getShape()->getChildren(l);
                    if (!AABB::isIntersect(shape1->getAABB(), shape2->getAABB())) {
                        collisionInfo->clean();
                        skiped++;
                        continue;
                    }
                    newCollisionsCount++;
                    std::vector<Collision *> collisions = CollisionFactory::createCollision(
                            (PolygonShape *) shape1, (PolygonShape *) shape2);
                    if (!collisions.empty()) {
                        collisionInfo->addConstraints(collisions);
                    } else {
                        collisionInfo->clean();
                    }
                }
            }
            if (!collisionInfo->isEmpty()) {
                collisionInfos1.push_back(collisionInfo);
            }
        }
    }
    LOGE("updateTime %f", now() - updateTime);

    LOGE("new collisions count %d", newCollisionsCount);

    LOGE("skiped %d", skiped);

    for (int i = 0; i < collisionInfos1.size(); i++) {
        collisionInfos1[i]->applyWarmStarting();
    }

    for (int iteration = 0; iteration < 5; iteration++) {
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
