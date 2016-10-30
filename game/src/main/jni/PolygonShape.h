//
// Created by qwerty on 10.09.16.
//

#ifndef PLATFORMER_POLYGON_H
#define PLATFORMER_POLYGON_H

#include "Vec2.h"
#include "BaseShape.h"
#include "VertexBuff.h"
#include "Line.h"
#include "Texture.h"
#include "DrawableShape.h"

class PolygonShape : public DrawableShape {
public:
    PolygonShape(Vec2 *vertices, int verticesSize, Texture *texture);

    PolygonShape(Vec2 *vertices, int verticesSize);

    virtual ~PolygonShape();

    Vec2 *getVertices() const;

    Line *getLines() const;

    int getVerticesSize() const;

    virtual void draw(float *mvp);

    virtual void innerRotate(float angle);

    virtual unsigned int type() const;

    virtual void move(const Vec2 &coords);

    Vec2 getVertex(int i) const;

    virtual void calculateInnerAABB();

    void setTexture(Texture *texture);

private:
    Vec2 *initVertices;
    Vec2 *vertices;
    Line *lines;
    int verticesSize;
    VertexBuff *vertexBuff;
    unsigned short *indices;

    Texture *texture;

    bool doesGlObjectsInitialized;

    void calculateLines();
};

#endif //PLATFORMER_POLYGON_H
