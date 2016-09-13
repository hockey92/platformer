//
// Created by qwerty on 10.09.16.
//

#include "PolygonShape.h"
#include "Shader.h"
#include "Shaders.h"
#include "ndk_helper/vecmath.h"
#include "ShapeTypes.h"

PolygonShape::PolygonShape(Vec2 *vertices, int verticesSize) {
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

void PolygonShape::draw(float *mvp) const {
    Shader *shader = Shaders::getSimpleShader();

    vertexBuff->init();

    shader->beginRender(vertexBuff, verticesSize, 4);
    shader->setColor(0.0f, 1.0f, 0.0f, 1.0f);
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
