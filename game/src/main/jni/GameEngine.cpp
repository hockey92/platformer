/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <GLES2/gl2.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "TextureShader.h"
#include "DrawUtils.h"
#include "PhysicsObject.h"
#include "BasePhysicsService.h"
#include "ndk_helper/vecmath.h"
#include "Shaders.h"
#include "PolygonShape.h"
#include "CollisionFactory.h"

#define  LOG_TAG    "accelerometergraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


BasePhysicsService *basePhysicsService = new BasePhysicsService();

class GameEngine {
    File *circle;
    TextureShader *shader;
    float mvp[16];
    Texture *texture;
    PolygonShape *polygon1;
    PolygonShape *polygon2;

    PolygonShape *c1;
    PolygonShape *c2;

    float penDepth;
    std::vector<std::pair<float, int> > pointNumbers;
    int lineNumber;

public:
    GameEngine() { }

    void init(AAssetManager *assetManager) {
        circle = new File("circle.tga", assetManager);
    }

    void surfaceCreated() {
        LOGI("GL_VERSION: %s", glGetString(GL_VERSION));
        LOGI("GL_VENDOR: %s", glGetString(GL_VENDOR));
        LOGI("GL_RENDERER: %s", glGetString(GL_RENDERER));
        LOGI("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));

        basePhysicsService->setStatus(PROCESSING);

        Shaders::compile();

        shader = Shaders::getTextureShader();

        texture = new Texture(new TGAImage(circle));

        Vec2 vertices1[] = {Vec2(0.9f, 0.1f),
                            Vec2(-0.9f, 0.1f),
                            Vec2(-0.9f, -0.1f),
                            Vec2(0.9f, -0.1f)};
        polygon1 = new PolygonShape(vertices1, 4);
        polygon1->move(Vec2(0, -1));

        Vec2 vertices2[] = {Vec2(0.0f, -0.2f),
                            Vec2(0.2f, 0.2f),
                            Vec2(-0.2f, 0.2f)};
        polygon2 = new PolygonShape(vertices2, 3);
        polygon2->move(Vec2(0, -0.7f));
        polygon2->rotate(0.2f);

//        Collision *collision = CollisionFactory::createCollision(polygon1, polygon2);

        Vec2 vertices3[] = {Vec2(0.02f, 0.02f),
                            Vec2(-0.02f, 0.02f),
                            Vec2(-0.02f, -0.02f),
                            Vec2(0.02f, -0.02f)};
        c1 = new PolygonShape(vertices3, 4);
//        c1->move(polygon2->getCenter() + collision->getR2());

        c2 = new PolygonShape(vertices3, 4);
//        c2->move(polygon1->getCenter() + collision->getR1());



//        Vec2 vertices1[] = {Vec2(0.5f, 0.5f),
//                            Vec2(-0.5f, 0.5f),
//                            Vec2(-0.5f, -0.5f),
//                            Vec2(0.5f, -0.5f)};
//        polygon1 = new PolygonShape(vertices1, 4);
//
//        Vec2 vertices2[] = {Vec2(0, 0),
//                            Vec2(-1, 0),
//                            Vec2(-1, -1),
//                            Vec2(0, -1)};
//        polygon2 = new PolygonShape(vertices2, 4);

//        polygon->rotate(0.2f);
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
        mvp[15] = 1.0f;
    }

    void update() {
        basePhysicsService->nextFrame();
    }

    void render() {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLineWidth(1.0f);
        glClearColor(1.f, 1.f, 1.f, 1.0f);

        polygon2->rotate(-0.01f);
//
        Collision *collision = CollisionFactory::createCollision(polygon1, polygon2);

        if (collision != NULL) {
            c1->setCenter(polygon2->getCenter() + collision->getR2());
            c2->setCenter(polygon1->getCenter() + collision->getR1());
            c1->draw(mvp);
            c2->draw(mvp);
        }

//        float *result = DrawUtils::createCoordsForTextureShader(-0.03f, 0.03f, -0.03f, 0.03f, 0.f,
//                                                                1.f, 0.f, 1.f);
//        VertexBuff *vertexBuff = new VertexBuff(result, 24);
//        delete[] result;
//
//        vertexBuff->init();
//        texture->init();
//
//        shader->beginRender(vertexBuff, 4, 6);
//        shader->setTexture(texture);
//        shader->setColor(0, 0, 1, 1);
//        for (int i = 0; i < basePhysicsService->physicsObjects.size(); i++) {
//            if (basePhysicsService->physicsObjects[i]->getShape()->type() != 1) {
//                continue;
//            }
//            shader->setMVP(
//                    (ndk_helper::Mat4(mvp) *
//                     ndk_helper::Mat4::Translation(
//                             basePhysicsService->physicsObjects[i]->getShape()->getCenter().x(),
//                             basePhysicsService->physicsObjects[i]->getShape()->getCenter().y(),
//                             0.0f)).Ptr()
//            );
//            shader->render();
//        }

        polygon1->draw(mvp);
        polygon2->draw(mvp);


        for (int i = 0; i < basePhysicsService->physicsObjects.size(); i++) {
            ((PolygonShape*) basePhysicsService->physicsObjects[i]->getShape())->draw(mvp);
        }

//        float penDepth;
//        std::vector<std::pair<float, int> > pointNumbers;
//        int lineNumber;
//        CollisionFactory::temp(polygon1, polygon2, penDepth, lineNumber, pointNumbers);
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
