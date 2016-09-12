//
// Created by qwerty on 10.09.16.
//

#include "Shaders.h"

Shaders Shaders::instance;

Shader *Shaders::getSimpleShader() {
    return &(instance.shader);
}

TextureShader *Shaders::getTextureShader() {
    return &(instance.textureShader);
}

void Shaders::compile() {
    instance.shader.compile();
    instance.textureShader.compile();
}
