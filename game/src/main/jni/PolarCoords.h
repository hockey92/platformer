//
// Created by qwerty on 03.10.16.
//

#ifndef PLATFORMER_POLARCOORDS_H
#define PLATFORMER_POLARCOORDS_H


class PolarCoords {
public:
    float angle;
    float r;

    PolarCoords(float angle, float r) : angle(angle), r(r) { }

    PolarCoords() { }

    void setValues(float angle, float r);
};

#endif //PLATFORMER_POLARCOORDS_H
