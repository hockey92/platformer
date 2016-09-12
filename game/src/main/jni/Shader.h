#ifndef NATIVE_ACTIVITY_SHADER_H
#define NATIVE_ACTIVITY_SHADER_H

#include "VertexBuff.h"
#include "Color.h"

class Shader {
protected:
    int vertShader, fragShader, program;
    int MVPMatrix;
    int positionAttrib;
    int colorAttrib;
    VertexBuff *preparedVertexBuf;

public:
    Shader();

    virtual ~Shader();

    virtual void compile();

    void bindShader();

    void unbindShader();

    virtual void beginRender(VertexBuff *vbuf, int size, int stride);

    void setMVP(float *mvp);

    void setColor(float r, float g, float b, float a);

    void setColor(const Color &color);

    // Renders one copy of the prepared geometry, given a model-view-projection matrix.
//    inline void Render(glm::mat4 *mvpMat) {
//        Render(NULL, mvpMat);
//    }

    // Renders a subset (given by the index buffer) of the prepared geometry, using
    // the given model-view-projection matrix.
    virtual void render();

    // Finishes rendering (call this after you're done making calls to Render())
    virtual void endRender();

    // Convenience method to render a single copy of a geometry.
//    inline void RenderSimpleGeom(glm::mat4* mvpMat, SimpleGeom *sg) {
//        beginRender(sg->vbuf);
//        Render(sg->ibuf, mvpMat);
//        endRender();
//    }
protected:
    // Push MVP matrix to the shader
//    void PushMVPMatrix(glm::mat4 *mat);

    // Push the vertex positions to the shader
    void PushPositions(int vbo_offset, int stride);

    virtual const char *getVertexShaderSource();

    virtual const char *getFragmentShaderSource();

    virtual const char *getShaderName();
};

#endif //NATIVE_ACTIVITY_SHADER_H
