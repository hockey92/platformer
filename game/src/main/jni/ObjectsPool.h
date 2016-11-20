//
// Created by qwerty on 16.10.16.
//

#ifndef PLATFORMER_OBJECTSPOOL_H
#define PLATFORMER_OBJECTSPOOL_H


#include "Mutex.h"

class ObjectsPool {
public:
    int addNewObject(void *object);

    void *getObject(int i);

    static ObjectsPool *getInstance();

private:
    ObjectsPool() : size(0) { }

    void *objects[1000];
    Mutex mutex;
    int size;

    static ObjectsPool INSTANCE;
};

#endif //PLATFORMER_OBJECTSPOOL_H
