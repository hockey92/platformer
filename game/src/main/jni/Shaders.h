//
// Created by qwerty on 10.09.16.
//

#ifndef PLATFORMER_SHADERS_H
#define PLATFORMER_SHADERS_H

#include "Shader.h"
#include "TextureShader.h"

class Shaders {
public:
    static Shader *getSimpleShader();

    static TextureShader *getTextureShader();

    static void compile();

private:
    Shaders() { }

    static Shaders instance;

    Shader shader;
    TextureShader textureShader;
};

#endif //PLATFORMER_SHADERS_H
