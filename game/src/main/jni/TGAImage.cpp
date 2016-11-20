#include <stddef.h>
#include "TGAImage.h"
#include "File.h"

struct TGAHeader {
    unsigned char idSize;
    unsigned char colorMapType;
    unsigned char imageType;
    unsigned short paletteStart;
    unsigned short paletteLength;
    unsigned char paletteBits;
    unsigned short xOrigin;
    unsigned short yOrigin;
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char descriptor;
} __attribute__ ((packed));

int TGAImage::getH() const {
    return h;
}

int TGAImage::getW() const {
    return w;
}

void *TGAImage::getPtr() const {
    return ptr;
}

TGAImage::TGAImage(File *file) : file(file) {
    w = ((TGAHeader *) file->buff())->width;
    h = ((TGAHeader *) file->buff())->height;
    ptr = (file->buff() + sizeof(TGAHeader));
}

Pixel TGAImage::getPixel(int y, int x) const {
    unsigned char *startPointer = ((unsigned char *) ptr) + y * w * 4 + x * 4;
    return Pixel(*startPointer, *(startPointer + 1), *(startPointer + 2), *(startPointer + 3));
}
