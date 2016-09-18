#include <jni.h>
#include <GLES2/gl2.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "TextureShader.h"
#include "PhysicsObject.h"
#include "BasePhysicsService.h"
#include "Shaders.h"
#include "PolygonShape.h"

#define  LOG_TAG    "accelerometergraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


BasePhysicsService *basePhysicsService = new BasePhysicsService();

class GameEngine {
    float mvp[16];

public:
    GameEngine() { }

    void init(AAssetManager *assetManager) {
    }

    void surfaceCreated() {
        LOGI("GL_VERSION: %s", glGetString(GL_VERSION));
        LOGI("GL_VENDOR: %s", glGetString(GL_VENDOR));
        LOGI("GL_RENDERER: %s", glGetString(GL_RENDERER));
        LOGI("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));

        basePhysicsService->setStatus(PROCESSING);

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

    void update() {
        basePhysicsService->nextFrame();
    }

    void render() {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLineWidth(1.5f);
        glClearColor(0.f, 0.f, 0.f, 1.0f);

        for (int i = 0; i < basePhysicsService->physicsObjects.size(); i++) {
            ((PolygonShape *) basePhysicsService->physicsObjects[i]->getShape())->draw(mvp);
        }
    }

    void pause() {
    }

    void resume() {
    }
};


GameEngine gameEngine;

extern "C" {
JNIEXPORT void JNICALL
Java_com_android_game_AccelerometerGraphJNI_init(
        JNIEnv *env, jclass type, jobject assetManager) {
    (void) type;
    AAssetManager *nativeAssetManager = AAssetManager_fromJava(env, assetManager);
    gameEngine.init(nativeAssetManager);
}

JNIEXPORT void JNICALL
Java_com_android_game_AccelerometerGraphJNI_surfaceCreated(JNIEnv *env, jclass type) {
    (void) env;
    (void) type;
    gameEngine.surfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_android_game_AccelerometerGraphJNI_surfaceChanged(
        JNIEnv *env, jclass type, jint width, jint height) {
    (void) env;
    (void) type;
    gameEngine.surfaceChanged(width, height);
}


JNIEXPORT void JNICALL
Java_com_android_game_AccelerometerGraphJNI_drawFrame(
        JNIEnv *env, jclass type) {
    (void) env;
    (void) type;
    gameEngine.render();
}

JNIEXPORT void JNICALL
Java_com_android_game_AccelerometerGraphJNI_pause(
        JNIEnv *env, jclass type) {
    (void) env;
    (void) type;
    gameEngine.update();
}

JNIEXPORT void JNICALL
Java_com_android_game_AccelerometerGraphJNI_resume(
        JNIEnv *env, jclass type) {
    (void) env;
    (void) type;
    gameEngine.resume();
}
}
