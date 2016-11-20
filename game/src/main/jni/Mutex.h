#ifndef INC_100BALLS_MUTEX_H
#define INC_100BALLS_MUTEX_H


#include <pthread.h>

class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&mutex, NULL);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex);
    }

    void lock() {
        pthread_mutex_lock(&mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;
};


#endif //INC_100BALLS_MUTEX_H
