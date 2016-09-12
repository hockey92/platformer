#include <GLES2/gl2.h>
#include "TextureShader.h"
#include "common.h"

struct TGAHeader {
    unsigned char m_idSize;
    unsigned char m_colorMapType;
    unsigned char m_imageType;
    unsigned short m_paletteStart;
    unsigned short m_paletteLength;
    unsigned char m_paletteBits;
    unsigned short m_xOrigin;
    unsigned short m_yOrigin;
    unsigned short m_width;
    unsigned short m_height;
    unsigned char m_bpp;
    unsigned char m_descriptor;
} __attribute__ ((packed));

const char *TextureShader::getShaderName() {
    return "TextureShader";
}

const char *TextureShader::getVertexShaderSource() {
    return "precision highp float; \n"
            "attribute vec4 a_Position; \n"
            "attribute vec2 a_texCoord; \n"
            "varying vec2 v_texCoord; \n"
            "uniform mat4 projection;   \n"
            "uniform vec4 a_Color;   \n"
            "varying vec4 v_Color; \n"
            "void main(){ \n"
            "   gl_Position = projection * a_Position; \n"
            "   v_texCoord = a_texCoord; \n"
            "   v_Color = a_Color; \n"
            "} \n";
}

const char *TextureShader::getFragmentShaderSource() {
    return "precision highp float; \n"
            "varying vec2 v_texCoord; \n"
            "uniform sampler2D s_texture; \n"
            "varying vec4 v_Color;          \n"
            "void main(){ \n"
            "   gl_FragColor = vec4(v_Color.r, v_Color.g, v_Color.b, v_Color.a * texture2D(s_texture, v_texCoord).a); \n"
            "} \n";
}

void TextureShader::compile() {
    Shader::compile();

    bindShader();
    texCoordAttributeHandle = glGetAttribLocation(program, "a_texCoord");
    if (texCoordAttributeHandle < 0) {
        LOGE("*** Couldn't get shader's a_texCoord location.");
        ABORT_GAME;
    }
    samplerHandle = glGetUniformLocation(program, "s_texture");
    if (samplerHandle < 0) {
        LOGE("*** Couldn't get shader's s_texture location.");
        ABORT_GAME;
    }
    unbindShader();
}

void TextureShader::setTexture(Texture *texture) {
    ASSERT(preparedVertexBuf != NULL);
    texture->bind(GL_TEXTURE0);
    glUniform1i(samplerHandle, 0);
}

void TextureShader::beginRender(VertexBuff *vbuf, int size, int stride) {
    Shader::beginRender(vbuf, size, stride);

    glVertexAttribPointer(texCoordAttributeHandle, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(4 * sizeof(float)));
    glEnableVertexAttribArray(texCoordAttributeHandle);
}

void TextureShader::render() {
    Shader::render();
    GLushort indices[] = {0, 1, 2, 0, 2, 3};
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}
