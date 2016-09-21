#include <jni.h>
#include <GLES2/gl2.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "PhysicsObject.h"
#include "PhysicsService.h"
#include "Shaders.h"
#include "RectanglePhysicsObject.h"

#define  LOG_TAG    "accelerometergraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


PhysicsService physicsService;

int nextObjectNumber = 0;
PhysicsObject *objects[500];

class GameEngine {
    float mvp[16];

public:
    GameEngine() { }

    void init(AAssetManager *assetManager) {
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(100.f, 1.f, 0.f))->move(Vec2(0, -20.f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 100.f, 0.f))->move(Vec2(20, 0.f)));
//
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 10.f, 1.f))->move(Vec2(5.0f, -14.5f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 10.f, 1.f))->move(Vec2(10.0f, -14.5f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 10.f, 1.f))->move(Vec2(15.0f, -14.5f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(12.f, 1.f, 1.f))->move(Vec2(10.0f, -9.0f)));
//
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 10.f, 1.f))->move(Vec2(5.0f, -3.5f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 10.f, 1.f))->move(Vec2(10.0f, -3.5f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(1.f, 10.f, 1.f))->move(Vec2(15.0f, -3.5f)));
//        physicsService.addPhysicsObject(
//                (new RectanglePhysicsObject(12.f, 1.f, 1.f))->move(Vec2(10.0f, 2.0f)));
//
//        PhysicsObject *cube = new RectanglePhysicsObject(10.f, 10.f, 0.5f);
//        cube->getShape()->move(Vec2(-60, 0));
//        cube->setVel(Vec2(40, 0));
//
//        physicsService.addPhysicsObject(cube);
    }

    void surfaceCreated() {
        Shaders::compile();
    }

    void surfaceChanged(float w, float h) {
        glViewport(0, 0, w, h);

        for (int i = 0; i < 16; i++) {
            mvp[i] = 0;
        }

        float rel = w / h;

        mvp[0] = 1.0f;
        mvp[5] = rel;
        mvp[10] = 1.0f;
        mvp[15] = 40.0f;
    }

    void render() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLineWidth(1.5f);
        glClearColor(0.f, 0.f, 0.f, 1.0f);

        physicsService.draw(mvp);
    }
};

GameEngine gameEngine;

extern "C" {
JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_init(JNIEnv *env, jclass type, jobject assetManager) {
    AAssetManager *nativeAssetManager = AAssetManager_fromJava(env, assetManager);
    gameEngine.init(nativeAssetManager);
}

JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_surfaceCreated(JNIEnv *env, jclass type) {
    gameEngine.surfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_surfaceChanged(JNIEnv *env, jclass type, jint width, jint height) {
    gameEngine.surfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_android_game_GameEngine_drawFrame(JNIEnv *env, jclass type) {
    gameEngine.render();
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
Java_com_android_game_RectanglePhysicsObject_createCube(JNIEnv *env, jclass type,
                                                        jfloat w, jfloat h, jfloat invM) {
    objects[nextObjectNumber] = new RectanglePhysicsObject(w, h, invM);
    return nextObjectNumber++;
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_move(JNIEnv *env, jclass type,
                                         jint id, jfloat x, jfloat y) {
    objects[id]->getShape()->move(Vec2(x, y));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsObject_setVel(JNIEnv *env, jclass type,
                                           jint id, jfloat vx, jfloat vy) {
    objects[id]->setVel(Vec2(vx, vy));
}

JNIEXPORT void JNICALL
Java_com_android_game_PhysicsService_add(JNIEnv *env, jclass type, jint id) {
    physicsService.addPhysicsObject(objects[id]);
}

}
