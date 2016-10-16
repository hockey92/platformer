//
// Created by qwerty on 16.10.16.
//

#include "ObjectsPool.h"

ObjectsPool ObjectsPool::INSTANCE;

int ObjectsPool::addNewObject(void *object) {
    int objectIndex;
    mutex.lock();
    objectIndex = size;
    objects[size] = object;
    size++;
    mutex.unlock();
    return objectIndex;
}

void *ObjectsPool::getObject(int i) {
    return objects[i];
}

ObjectsPool *ObjectsPool::getInstance() {
    return &INSTANCE;
}