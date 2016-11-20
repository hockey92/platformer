#include <stddef.h>
#include <pthread.h>
#include "IThread.h"

IThread::IThread() : isStop(true) {

}

void IThread::start() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    isStop = false;

    pthread_create(&thread, &attr, run, this);
}

void *IThread::run(void *arg) {
    ((IThread *) arg)->innerRun();
    return NULL;
}
