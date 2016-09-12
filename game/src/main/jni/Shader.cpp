#include "Shader.h"
#include "common.h"

Shader::Shader() {
    vertShader = 0;
    fragShader = 0;
    program = 0;
}

Shader::~Shader() {
    if (vertShader) {
        glDeleteShader(vertShader);
        vertShader = 0;
    }
    if (fragShader) {
        glDeleteShader(fragShader);
        fragShader = 0;
    }
    if (program) {
        glDeleteProgram(program);
        program = 0;
    }
}

const char *Shader::getShaderName() {
    return "Shader";
}

const char *Shader::getVertexShaderSource() {
    return "attribute vec4 a_Position; \n"
            "uniform vec4 a_Color;   \n"
            "varying vec4 v_Color;     \n"
            "uniform mat4 projection; \n"
            "void main() \n"
            "{ \n"
            "     gl_Position = projection * a_Position; \n"
            "     v_Color = a_Color;          \n"
            "} \n";
}

const char *Shader::getFragmentShaderSource() {
    return "precision mediump float; \n"
            "varying vec4 v_Color;          \n"
            "void main() { \n"
            "    gl_FragColor = v_Color; \n"
            "} \n";
}

static void _printShaderLog(GLuint shader) {
    char buf[2048];
    memset(buf, 0, sizeof(buf));
    LOGE("*** Getting info log for shader %u", shader);
    glGetShaderInfoLog(shader, sizeof(buf) - 1, NULL, buf);
    LOGE("*** Info log:\n%s", buf);
}

static void _printProgramLog(GLuint program) {
    char buf[2048];
    memset(buf, 0, sizeof(buf));
    LOGE("*** Getting info log for program %u", program);
    glGetProgramInfoLog(program, sizeof(buf) - 1, NULL, buf);
    LOGE("*** Info log:\n%s", buf);
}

void Shader::compile() {
    const char *vsrc = 0, *fsrc = 0;
    GLint status = 0;

    LOGD("Compiling shader.");
    LOGD("Shader name: %s", getShaderName());

    vsrc = getVertexShaderSource();
    fsrc = getFragmentShaderSource();

    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader) {
        LOGE("*** Failed to create shader.");
        ABORT_GAME;
    }
    glShaderSource(vertShader, 1, &vsrc, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        LOGE("*** Vertex shader compilation failed.");
        _printShaderLog(vertShader);
        ABORT_GAME;
    }
    LOGD("Vertex shader compilation succeeded.");

    glShaderSource(fragShader, 1, &fsrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        LOGE("*** Fragment shader compilation failed, %d", status);
        _printShaderLog(fragShader);
        ABORT_GAME;
    }
    LOGD("Fragment shader compilation succeeded.");

    program = glCreateProgram();
    if (!program) {
        LOGE("*** Failed to create program");
        _printProgramLog(program);
        ABORT_GAME;
    }

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == 0) {
        LOGE("*** Shader program link failed, %d", status);
        ABORT_GAME;
    }
    LOGD("Program linking succeeded.");

    glUseProgram(program);
    MVPMatrix = glGetUniformLocation(program, "projection");
    if (MVPMatrix < 0) {
        LOGE("*** Couldn't get shader's u_MVP matrix location from shader.");
        ABORT_GAME;
    }
    positionAttrib = glGetAttribLocation(program, "a_Position");
    if (positionAttrib < 0) {
        LOGE("*** Couldn't get shader's a_Position attribute location.");
        ABORT_GAME;
    }
    LOGD("Shader compilation/linking successful.");

    colorAttrib = glGetUniformLocation(program, "a_Color");
    if (colorAttrib < 0) {
        LOGE("*** Couldn't get shader's a_Color attribute location.");
        ABORT_GAME;
    }
    LOGD("Shader compilation/linking successful.");

    glUseProgram(0);
}

void Shader::bindShader() {
    if (program == 0) {
        LOGW("!!! WARNING: attempt to use shader before compiling.");
        LOGW("!!! Compiling now. Shader: %s", getShaderName());
        compile();
    }
    glUseProgram(program);
}

void Shader::unbindShader() {
    glUseProgram(0);
}

// To be called by child classes only.
//void Shader::PushMVPMatrix(glm::mat4 *mat) {
//    ASSERT(mMVPMatrixLoc >= 0);
//    glUniformMatrix4fv(mMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(*mat));
//}

// To be called by child classes only.
void Shader::PushPositions(int vbo_offset, int stride) {
//    ASSERT(mPositionAttribLoc >= 0);
//    glVertexAttribPointer(mPositionAttribLoc, 3, GL_FLOAT, GL_FALSE, stride,
//                          BUFFER_OFFSET(vbo_offset));
//    glEnableVertexAttribArray(mPositionAttribLoc);
}

void Shader::beginRender(VertexBuff *vbuf, int size, int stride) {
    bindShader();
    vbuf->bind();

    ASSERT(positionAttrib >= 0);
    glVertexAttribPointer(positionAttrib, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(positionAttrib);

    // push positions to shader
//    PushPositions(vbuf->GetPositionsOffset(), vbuf->GetStride());

    preparedVertexBuf = vbuf;
}

void Shader::render() {
    ASSERT(preparedVertexBuf != NULL);

//    GLushort indices[] = {0, 1, 2, 0, 2, 3};
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    // push MVP matrix to shader
//    PushMVPMatrix(mvpMat);

//    if (ibuf) {
    // draw with index buffer
//        ibuf->BindBuffer();
//        glDrawElements(mPreparedVertexBuf->GetPrimitive(), ibuf->GetCount(), GL_UNSIGNED_SHORT,
//                       BUFFER_OFFSET(0));
//        ibuf->UnbindBuffer();
//    } else {
    // draw straight from vertex buffer
//        glDrawArrays(GL_TRIANGLES, 0, 4);
//    }
}

void Shader::endRender() {
    if (preparedVertexBuf) {
        preparedVertexBuf->unbind();
        preparedVertexBuf = NULL;
    }
}

void Shader::setMVP(float *mvp) {
    glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, mvp);
}

void Shader::setColor(float r, float g, float b, float a) {
    glUniform4f(colorAttrib, r, g, b, a);
}

void Shader::setColor(const Color &color) {
    glUniform4f(colorAttrib, color.r(), color.g(), color.b(), color.a());
}
