#ifndef TEAPOT_SEGMENT_H
#define TEAPOT_SEGMENT_H

#include "Vec2.h"
#include "BaseShape.h"
#include "ShapeTypes.h"

class SegmentShape : public BaseShape {

public:
    SegmentShape() { }

    SegmentShape(Vec2 p1, Vec2 p2);

    SegmentShape(BaseShape *parent, Vec2 p1, Vec2 p2);

    Vec2 get(int i) const;

    Vec2 getPoint(int i) const;

    virtual unsigned int type() const;

    virtual void innerRotate(float angle);

    virtual void calculateInnerAABB();

protected:
    void init(Vec2 p1, Vec2 p2);

private:
    Vec2 points[2];
    Vec2 initPoints[2];
};

#endif //TEAPOT_SEGMENT_H
