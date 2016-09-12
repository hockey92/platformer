#include "VertexBuff.h"
#include "DrawUtils.h"

VertexBuff::VertexBuff(GLfloat *vertices, int size) {
    arrayWrapper.setValues(vertices, size);
}

void VertexBuff::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuff::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuff::~VertexBuff() {
    kill();
}

VertexBuff::VertexBuff(const AABB &aabb, float z) {
    float left;
    float right;
    float up;
    float down;
    aabb.getCoords(left, right, up, down);
    float indices[] = {right, up, z, 1.0f, left, up, z, 1.0f, left, down, z, 1.0f, right, down, z,
                       1.0f};
    arrayWrapper.setValues(indices, 16);
}

bool VertexBuff::init() {
    vbo = 0;

    glGenBuffers(1, &vbo);
    bind();
    glBufferData(GL_ARRAY_BUFFER, arrayWrapper.size() * sizeof(float), arrayWrapper.ptr(),
                 GL_STATIC_DRAW);
    unbind();
    return true;
}

void VertexBuff::kill() {
    glDeleteBuffers(1, &vbo);
}

VertexBuff::VertexBuff(Vec2 *vertices, int size) {
    float *result = DrawUtils::createCoordsForShader(vertices, 0, size);
    arrayWrapper.setValues(result, size * 4);
    delete[] result;
}
