#ifndef NATIVE_ACTIVITY_OPENGLOBJECTS_H
#define NATIVE_ACTIVITY_OPENGLOBJECTS_H

class OpenGLObject {
public:
    virtual bool init() = 0;

    virtual void kill() = 0;
};

#endif //NATIVE_ACTIVITY_OPENGLOBJECTS_H
