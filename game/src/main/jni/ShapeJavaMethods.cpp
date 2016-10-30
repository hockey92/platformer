//
// Created by qwerty on 16.10.16.
//

#include <jni.h>

#include "PhysicsObject.h"
#include "ObjectsPool.h"
#include "Joint.h"
#include "PolygonShape.h"
#include "FileManager.h"

extern "C" {

JNIEXPORT void JNICALL
Java_com_android_game_Shape_addChild(JNIEnv *env, jclass type,
                                     jint id, jint childrenId) {
    ((BaseShape *) ObjectsPool::getInstance()->getObject(id))
            ->addChild((BaseShape *) ObjectsPool::getInstance()->getObject(childrenId));
}

JNIEXPORT void JNICALL
Java_com_android_game_Shape_update(JNIEnv *env, jclass type, jint id) {
    ((BaseShape *) ObjectsPool::getInstance()->getObject(id))->update();
}

JNIEXPORT void JNICALL
Java_com_android_game_Shape_setAngle(JNIEnv *env, jclass type, jint id, jfloat angle) {
    ((BaseShape *) ObjectsPool::getInstance()->getObject(id))->setAngle(angle);
    ((BaseShape *) ObjectsPool::getInstance()->getObject(id))->rotate(0);
}

JNIEXPORT jint JNICALL
Java_com_android_game_Joint_createJoint(JNIEnv *env, jclass type,
                                        jfloat parentAngle, jfloat parentR,
                                        jfloat childAngle, jfloat childR) {
    return ObjectsPool::getInstance()->addNewObject(new Joint(PolarCoords(parentAngle, parentR),
                                                              PolarCoords(childAngle, childR)));
}

JNIEXPORT jint JNICALL
Java_com_android_game_PolygonShape_createPolygon(JNIEnv *env, jclass type, jfloatArray arr) {
    jsize size = env->GetArrayLength(arr);
    jfloat *verticesArray = env->GetFloatArrayElements(arr, 0);
    Vec2 *vertices = new Vec2[size / 2];
    for (int i = 0; i < size / 2; i++) {
        vertices[i] = Vec2(verticesArray[i * 2], verticesArray[i * 2 + 1]);
    }
    int newObjectIndex = ObjectsPool::getInstance()
            ->addNewObject(new PolygonShape(vertices, size / 2));
    env->ReleaseFloatArrayElements(arr, verticesArray, 0);
    return newObjectIndex;
}

JNIEXPORT jint JNICALL
Java_com_android_game_PolygonShape_createPolygonWithTexture(JNIEnv *env, jclass type,
                                                            jfloatArray arr, jstring fileName) {
    jsize size = env->GetArrayLength(arr);
    jfloat *verticesArray = env->GetFloatArrayElements(arr, 0);
    Vec2 *vertices = new Vec2[size / 2];
    for (int i = 0; i < size / 2; i++) {
        vertices[i] = Vec2(verticesArray[i * 2], verticesArray[i * 2 + 1]);
    }

    const char *cFileName = env->GetStringUTFChars(fileName, 0);
    int stringLen = env->GetStringLength(fileName);

    char cFileNameCopy[stringLen];
    for (int i = 0; i < stringLen; i++) {
        cFileNameCopy[i] = cFileName[i];
    }

    File *file = FileManager::getInstance()->getFile(std::string(cFileName));

    int newObjectIndex = ObjectsPool::getInstance()->addNewObject(
            new PolygonShape(vertices, size / 2, new Texture(new TGAImage(file))));

    env->ReleaseStringUTFChars(fileName, cFileName);
    env->ReleaseFloatArrayElements(arr, verticesArray, 0);
    return newObjectIndex;
}

JNIEXPORT void JNICALL
Java_com_android_game_Shape_move(JNIEnv *env, jclass type, jint id, jfloat x, jfloat y) {
    ((BaseShape *) ObjectsPool::getInstance()->getObject(id))->move(Vec2(x, y));
}

JNIEXPORT void JNICALL
Java_com_android_game_Shape_setCenter(JNIEnv *env, jclass type, jint id, jfloat x, jfloat y) {
    ((BaseShape *) ObjectsPool::getInstance()->getObject(id))->setCenter(Vec2(x, y));
}

JNIEXPORT jobject JNICALL
Java_com_android_game_Shape_getCenter(JNIEnv *env, jclass type, jint id) {
    Vec2 vel = ((BaseShape *) ObjectsPool::getInstance()->getObject(id))->getCenter();
    jclass cls = env->FindClass("com/android/game/Vec2");
    jmethodID methodID = env->GetMethodID(cls, "<init>", "(FF)V");
    return env->NewObject(cls, methodID, vel.x(), vel.y());
}

JNIEXPORT void JNICALL
Java_com_android_game_Shape_setVisible(JNIEnv *env, jclass type, jint id, jboolean visible) {
    ((DrawableShape *) ObjectsPool::getInstance()->getObject(id))->setVisible(visible);
}

}
