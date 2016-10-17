//
// Created by qwerty on 10.09.16.
//

#include "PolygonShape.h"
#include "Shader.h"
#include "Shaders.h"
#include "ndk_helper/vecmath.h"
#include "ShapeTypes.h"

PolygonShape::PolygonShape(Vec2 *vertices, int verticesSize) {

    isVertexBuffInited = false;

    this->initVertices = new Vec2[verticesSize];
    this->vertices = new Vec2[verticesSize];
    for (int i = 0; i < verticesSize; i++) {
        this->initVertices[i] = vertices[i];
        this->vertices[i] = vertices[i];
    }
    vertexBuff = new VertexBuff(vertices, verticesSize);
    this->verticesSize = verticesSize;

    indices = new unsigned short[2 * verticesSize];
    for (int i = 0; i < verticesSize; i++) {
        indices[2 * i] = i;
        indices[2 * i + 1] = i == verticesSize - 1 ? 0 : i + 1;
    }

    lines = new Line[verticesSize];
    calculateLines();
    calculateAABB();
}

PolygonShape::~PolygonShape() {
    delete[] initVertices;
    delete[] vertices;
    delete[] indices;
    delete vertexBuff;
}

Vec2 *PolygonShape::getVertices() const {
    return vertices;
}

void PolygonShape::draw(float *mvp) {
    Shader *shader = Shaders::getSimpleShader();

    if (!isVertexBuffInited) {
        vertexBuff->init();
        isVertexBuffInited = true;
    }

    shader->beginRender(vertexBuff, verticesSize, 4);
    shader->setColor(1.0f, 1.0f, 1.0f, 1.0f);
    shader->setMVP((ndk_helper::Mat4(mvp) *
                    ndk_helper::Mat4::Translation(center.x(), center.y(), 0.0f) *
                    ndk_helper::Mat4::RotationZ(-angle)).Ptr());

    glDrawElements(GL_LINES, verticesSize * 2, GL_UNSIGNED_SHORT, indices);
}

void PolygonShape::calculateLines() {
    for (int i = 0; i < verticesSize; i++) {
        lines[i].calculate(getVertex(indices[i * 2 + 1]), getVertex(indices[i * 2]));
    }
}

int PolygonShape::getVerticesSize() const {
    return verticesSize;
}

Line *PolygonShape::getLines() const {
    return lines;
}

void PolygonShape::innerRotate(float angle) {
    BaseShape::innerRotate(angle);
    for (int i = 0; i < verticesSize; i++) {
        vertices[i] = initVertices[i].rotate(getAngel());
    }
    calculateLines();
}

unsigned int PolygonShape::type() const {
    return ShapeTypes::POLYGON;
}

void PolygonShape::move(const Vec2 &coords) {
    BaseShape::move(coords);
    calculateLines();
}

Vec2 PolygonShape::getVertex(int i) const {
    return vertices[i] + center;
}

void PolygonShape::calculateInnerAABB() {
    float minX = 1000000, maxX = -1000000;
    float minY = 1000000, maxY = -1000000;
    for (int i = 0; i < verticesSize; i++) {
        Vec2 realVertex = getVertex(i);
        if (realVertex.x() >= maxX) {
            maxX = realVertex.x();
        }
        if (realVertex.x() <= minX) {
            minX = realVertex.x();
        }
        if (realVertex.y() >= maxY) {
            maxY = realVertex.y();
        }
        if (realVertex.y() <= minY) {
            minY = realVertex.y();
        }
    }
    if (aabb == NULL) {
        aabb = new AABB(minX, minY, maxX, maxY);
    } else {
        aabb->set(minX, minY, maxX, maxY);
    }
}
