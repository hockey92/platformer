#ifndef NATIVE_ACTIVITY_ARRAYWRAPPER_H
#define NATIVE_ACTIVITY_ARRAYWRAPPER_H

#include <stddef.h>
#include <pthread.h>

class ArrayWrapper {
public:
    ArrayWrapper() : _size(0), _array(NULL) { }

    virtual ~ArrayWrapper();

    void setValues(float *array, int size);

    float get(int i) const;

    int size() const;

    ArrayWrapper & operator=(const ArrayWrapper &a);

    float *ptr() const {
        return _array;
    }

private:
    int _size;
    float *_array;

    void setSize(int size);
};

#endif //NATIVE_ACTIVITY_ARRAYWRAPPER_H
