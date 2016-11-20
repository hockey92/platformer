#include "DrawUtils.h"

float *DrawUtils::createCoordsForTextureShader(float down, float up, float left, float right,
                                               float texDown, float texUp,
                                               float texLeft, float texRight) {
    float *result = new float[4 * 6];
    result[0] = left, result[1] = down, result[2] = 0.0f, result[3] = 1.0f;
    result[4] = texLeft, result[5] = texDown;
    result[6] = left, result[7] = up, result[8] = 0.0f, result[9] = 1.0f;
    result[10] = texLeft, result[11] = texUp;
    result[12] = right, result[13] = up, result[14] = 0.0f, result[15] = 1.0f;
    result[16] = texRight, result[17] = texUp;
    result[18] = right, result[19] = down, result[20] = 0.0f, result[21] = 1.0f;
    result[22] = texRight, result[23] = texDown;
    return result;
}

float *DrawUtils::createCoordsForShader(float *xyCoords, float zCoord, int size) {
    float *result = new float[size * 4];
    for (int i = 0; i < size; i++) {
        result[i * 4] = xyCoords[i * 2];
        result[i * 4 + 1] = xyCoords[i * 2 + 1];
        result[i * 4 + 2] = zCoord;
        result[i * 4 + 3] = 1.0f;
    }
    return result;
}

float *DrawUtils::createCoordsForShader(Vec2* vertices, float zCoord, int size) {
    float *result = new float[size * 4];
    for (int i = 0; i < size; i++) {
        result[i * 4] = vertices[i].x();
        result[i * 4 + 1] = vertices[i].y();
        result[i * 4 + 2] = zCoord;
        result[i * 4 + 3] = 1.0f;
    }
    return result;
}
