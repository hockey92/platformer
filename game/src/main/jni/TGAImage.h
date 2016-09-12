#ifndef NATIVE_ACTIVITY_IMAGE_H
#define NATIVE_ACTIVITY_IMAGE_H

#include "File.h"

struct Pixel {

    Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) : r(r), g(g), b(b), alpha(alpha) { }

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char alpha;
};

class TGAImage {
public:
    TGAImage(File *file);

    int getH() const;

    int getW() const;

    void *getPtr() const;

    Pixel getPixel(int y, int x) const;

private:
    File *file;
    void *ptr;
    int w;
    int h;
};

#endif //NATIVE_ACTIVITY_IMAGE_H
