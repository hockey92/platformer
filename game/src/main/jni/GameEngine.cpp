#include <jni.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "PhysicsObject.h"
#include "PhysicsService.h"
#include "RectanglePhysicsObject.h"
#include "ScreenService.h"
#include "PolygonShape.h"
#include "ObjectsPool.h"

#define  LOG_TAG    "accelerometergraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

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

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsService_add(JNIEnv *env, jclass type, jint id) {
    physicsService.addPhysicsObject((PhysicsObject *) ObjectsPool::getInstance()->getObject(id));
//    screenService.add(((PhysicsObject *) ObjectsPool::getInstance()->getObject(id))->getShape());
}

JNIEXPORT void JNICALL
Java_com_android_game_ScreenService_add(JNIEnv *env, jclass type, jint id) {
    screenService.add((BaseShape *) ObjectsPool::getInstance()->getObject(id));
}

}
