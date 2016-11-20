#include "SegmentShape.h"
#include "AABB.h"

#ifndef NATIVE_ACTIVITY_CIRCLE_H
#define NATIVE_ACTIVITY_CIRCLE_H

class CircleShape : public BaseShape {

public:
    CircleShape(float r);

    float getR() const;

    virtual unsigned int type() const;

    virtual void calculateInnerAABB();

private:
    float r;
};

#endif //NATIVE_ACTIVITY_CIRCLE_H
