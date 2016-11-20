//
// Created by qwerty on 13.11.16.
//

#include "Cube.h"
#include "Shaders.h"

Cube::Cube(float x, float y, float z) : x(x), y(y), z(z) {
    float halfX = x / 2.f;
    float halfY = y / 2.f;
    float halfZ = z / 2.f;

    float vertices[] = {halfX, halfY, halfZ, 1.0f,
                        -halfX, halfY, halfZ, 1.0f,
                        -halfX, -halfY, halfZ, 1.0f,
                        halfX, -halfY, halfZ, 1.0f,

                        halfX, halfY, -halfZ, 1.0f,
                        halfX, -halfY, -halfZ, 1.0f,
                        -halfX, -halfY, -halfZ, 1.0f,
                        -halfX, halfY, -halfZ, 1.0f,

                        halfX, halfY, halfZ, 1.0f,
                        -halfX, halfY, halfZ, 1.0f,
                        -halfX, halfY, -halfZ, 1.0f,
                        halfX, halfY, -halfZ, 1.0f,

                        halfX, -halfY, halfZ, 1.0f,
                        -halfX, -halfY, halfZ, 1.0f,
                        -halfX, -halfY, -halfZ, 1.0f,
                        halfX, -halfY, -halfZ, 1.0f,

                        halfX, halfY, halfZ, 1.0f,
                        halfX, -halfY, halfZ, 1.0f,
                        halfX, -halfY, -halfZ, 1.0f,
                        halfX, halfY, -halfZ, 1.0f,

                        -halfX, halfY, halfZ, 1.0f,
                        -halfX, -halfY, halfZ, 1.0f,
                        -halfX, -halfY, -halfZ, 1.0f,
                        -halfX, halfY, -halfZ, 1.0f
    };

    vertexBuff = new VertexBuff(vertices, 96);
}

void Cube::init() {
    vertexBuff->init();
}


void Cube::draw(float *mvp) {
    Shader *shader = Shaders::getSimpleShader();

    shader->beginRender(vertexBuff, 4, 4);
    shader->setMVP(mvp);

    Color colors[6] = {Color(1, 0, 0, 1),
                       Color(0, 1, 0, 1),
                       Color(0, 0, 1, 1),
                       Color(1, 1, 0, 1),
                       Color(1, 0, 1, 1),
                       Color(0, 1, 1, 1)};

    for (int i = 0; i < 6; i++) {
        shader->setColor(colors[i]);

        GLushort indices[] = {0 + i * 4, 1 + i * 4, 2 + i * 4,
                              0 + i * 4, 2 + i * 4, 3 + i * 4};

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    }
}
