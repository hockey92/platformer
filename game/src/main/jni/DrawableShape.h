//
// Created by qwerty on 30.10.16.
//

#ifndef PLATFORMER_DRAWABLESHAPE_H
#define PLATFORMER_DRAWABLESHAPE_H


#include "BaseShape.h"

class DrawableShape : public BaseShape {
public:

    DrawableShape() : visible(true) { }

    virtual void draw(float *mvp) { }

    void setVisible(bool visible) {
        this->visible = visible;
    }

    bool isVisible() {
        return visible;
    }

private:
    bool visible;
};


#endif //PLATFORMER_DRAWABLESHAPE_H
