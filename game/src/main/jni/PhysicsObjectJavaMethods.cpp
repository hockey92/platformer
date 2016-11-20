//
// Created by qwerty on 16.10.16.
//

#include <jni.h>
#include "PhysicsObject.h"
#include "ObjectsPool.h"
#include "RectanglePhysicsObject.h"

extern "C" {
JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_move(JNIEnv *env, jclass type,
                                         jint id, jfloat x, jfloat y) {
    ((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))->getShape()->move(Vec2(x, y));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setVel(JNIEnv *env, jclass type,
                                           jint id, jfloat vx, jfloat vy) {
    ((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))->setVel(Vec2(vx, vy));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setAcceleration(JNIEnv *env, jclass type,
                                                    jint id, jfloat ax, jfloat ay) {
    ((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))->setAcceleration(Vec2(ax, ay));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setVelThreshold(JNIEnv *env, jclass type,
                                                    jint id, jfloat tx, jfloat ty) {
    ((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))->setVelThreshold(Vec2(tx, ty));
}

JNIEXPORT jobject JNICALL
Java_com_android_game_PhysicsObject_getVel(JNIEnv *env, jclass type, jint id) {
    Vec2 vel = ((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))->getVel();
    jclass cls = env->FindClass("com/android/game/Vec2");
    jmethodID methodID = env->GetMethodID(cls, "<init>", "(FF)V");
    return env->NewObject(cls, methodID, vel.x(), vel.y());
}

JNIEXPORT jobject JNICALL
Java_com_android_game_PhysicsObject_getCenter(JNIEnv *env, jclass type, jint id) {
    Vec2 vel = ((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))
            ->getShape()->getCenter();
    jclass cls = env->FindClass("com/android/game/Vec2");
    jmethodID methodID = env->GetMethodID(cls, "<init>", "(FF)V");
    return env->NewObject(cls, methodID, vel.x(), vel.y());
}

JNIEXPORT jint JNICALL
Java_com_android_game_PhysicsObject_createPhysicsObject(JNIEnv *env, jclass type,
                                                      jint shapeId, jfloat invM, jfloat invI) {
    BaseShape *shape = (BaseShape *) ObjectsPool::getInstance()->getObject(shapeId);
    return ObjectsPool::getInstance()->addNewObject(new PhysicsObject(shape, invM, invI));
}

}
