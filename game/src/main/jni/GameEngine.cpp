#include <jni.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "PhysicsObject.h"
#include "PhysicsService.h"
#include "RectanglePhysicsObject.h"
#include "ScreenService.h"

#define  LOG_TAG    "accelerometergraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

int nextObjectNumber = 0;
void *objects[500];

PhysicsService physicsService;
ScreenService screenService;

extern "C" {
JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_init(JNIEnv *env, jclass type, jobject assetManager) {
//    AAssetManager *nativeAssetManager = AAssetManager_fromJava(env, assetManager);
//    gameEngine.init(nativeAssetManager);
}

JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_surfaceCreated(JNIEnv *env, jclass type) {
    screenService.surfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_surfaceChanged(JNIEnv *env, jclass type, jint width, jint height) {
    screenService.surfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_drawFrame(JNIEnv *env, jclass type) {
    screenService.draw();
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsService_nextFrame(JNIEnv *env, jclass type) {
    physicsService.nextFrame();
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsService_start(JNIEnv *env, jclass type) {
    physicsService.setStatus(PROCESSING);
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsService_stop(JNIEnv *env, jclass type) {
    physicsService.setStatus(PAUSED);
}

JNIEXPORT jint JNICALL
Java_com_android_game_RectanglePO_createCube(JNIEnv *env, jclass type,
                                             jfloat w, jfloat h, jfloat invM) {
    objects[nextObjectNumber] = new RectanglePhysicsObject(w, h, invM);
    return nextObjectNumber++;
}

JNIEXPORT jint JNICALL
Java_com_android_game_Shape_createShape(JNIEnv *env, jclass type, jobjectArray arr) {

}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_move(JNIEnv *env, jclass type,
                                         jint id, jfloat x, jfloat y) {
    ((PhysicsObject *) objects[id])->getShape()->move(Vec2(x, y));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setVel(JNIEnv *env, jclass type,
                                           jint id, jfloat vx, jfloat vy) {
    ((PhysicsObject *) objects[id])->setVel(Vec2(vx, vy));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setAcceleration(JNIEnv *env, jclass type,
                                                    jint id, jfloat ax, jfloat ay) {
    ((PhysicsObject *) objects[id])->setAcceleration(Vec2(ax, ay));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setVelThreshold(JNIEnv *env, jclass type,
                                                    jint id, jfloat tx, jfloat ty) {
    ((PhysicsObject *) objects[id])->setVelThreshold(Vec2(tx, ty));
}

JNIEXPORT jobject JNICALL
Java_com_android_game_PhysicsObject_getVel(JNIEnv *env, jclass type, jint id) {
    Vec2 vel = ((PhysicsObject *) objects[id])->getVel();
    jclass cls = env->FindClass("com/android/game/Vec2");
    jmethodID methodID = env->GetMethodID(cls, "<init>", "(FF)V");
    return env->NewObject(cls, methodID, vel.x(), vel.y());
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsService_add(JNIEnv *env, jclass type, jint id) {
    physicsService.addPhysicsObject((PhysicsObject*) objects[id]);
    screenService.add(((PhysicsObject*) objects[id])->getShape());
}

}
