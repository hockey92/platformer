#ifndef INC_100BALLS_ITHREAD_H
#define INC_100BALLS_ITHREAD_H


class IThread {

public:
    IThread();

    void start();

protected:
    virtual void innerRun() = 0;

    bool isStop;

private:
    pthread_t thread;

    static void *run(void *arg);
};

#endif //INC_100BALLS_ITHREAD_H
