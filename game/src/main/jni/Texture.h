#ifndef NATIVE_ACTIVITY_TEXTURE_H
#define NATIVE_ACTIVITY_TEXTURE_H

#include <GLES2/gl2.h>
#include "File.h"
#include "TGAImage.h"

class Texture {
private:
    GLuint texture;
    TGAImage *image;

public:
    Texture(TGAImage *image);

    virtual ~Texture();

    void init();

    void bind(int unit);

    void unbind();
};

#endif //NATIVE_ACTIVITY_TEXTURE_H
