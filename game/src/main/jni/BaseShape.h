#ifndef TEAPOT_BASESHAPE_H
#define TEAPOT_BASESHAPE_H

#include <cstddef>
#include "Vec2.h"
#include "AABB.h"

class BaseShape {
public:
    BaseShape();

    virtual ~BaseShape();

    void update();

    virtual void move(const Vec2 &coords);

    void rotate(const float angle);

    Vec2 getCenter() const;

    void setCenter(const Vec2 &center);

    float getAngel() const;

    virtual int getSimpleShapesCount() const;

    virtual unsigned int type() const;

    virtual BaseShape *getChildren(int i);

    void calculateExtendAABB(const Vec2 &moveVec);

    AABB *getExtendedAABB();

    AABB *getAABB();

    virtual void calculateInnerAABB();

    virtual void calculateAABB();

    virtual void getVertices(float *vertices) { }

    virtual int verticesSize() { return -1; }

    float getZ();

    void setZ(float z);

    virtual void draw(float *mvp) const { }

    void setAngle(float angle);

    void addChild(BaseShape *baseShape);

protected:
    Vec2 center;
    int realChildCount;
    float angle;
    BaseShape *children[20];
    BaseShape *parent;
    AABB *aabb;
    AABB *extendedAABB;
    float z;

    void setParent(BaseShape *parent) { this->parent = parent; }

    virtual void innerRotate(float angle);

    virtual void innerUpdate() { }
};

#endif //TEAPOT_BASESHAPE_H
