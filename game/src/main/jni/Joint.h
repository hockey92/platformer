//
// Created by qwerty on 02.10.16.
//

#ifndef PLATFORMER_JOINT_H
#define PLATFORMER_JOINT_H


#include "BaseShape.h"
#include "PolarCoords.h"

class Joint : public BaseShape {
public:
    Joint(PolarCoords parentPolarCoords, PolarCoords childPolarCoords);

    void setAngleBetweenParentAndChild(float angleBetweenParentAndChild) {
        this->angleBetweenParentAndChild = angleBetweenParentAndChild;
    }

    float getAngleBetweenParentAndChild() {
        return angleBetweenParentAndChild;
    }

private:
    PolarCoords parentPolarCoords;
    PolarCoords childPolarCoords;

    float angleBetweenParentAndChild;

    virtual void innerUpdate();
};

#endif //PLATFORMER_JOINT_H
