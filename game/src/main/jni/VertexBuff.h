#ifndef NATIVE_ACTIVITY_VERTEXBUFF_H
#define NATIVE_ACTIVITY_VERTEXBUFF_H

#include <GLES2/gl2.h>
#include "AABB.h"
#include "ArrayWrapper.h"
#include "OpenGLObject.h"

class VertexBuff : public OpenGLObject {
public:
    VertexBuff(GLfloat *vertices, int size);

    VertexBuff(Vec2 *vertices, int size);

    VertexBuff(const AABB &aabb, float z);

    virtual ~VertexBuff();

    bool init();

    void kill();

    void bind();

    void unbind();

private:
    GLuint vbo;
    ArrayWrapper arrayWrapper;
};

#endif //NATIVE_ACTIVITY_VERTEXBUFF_H
