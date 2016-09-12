#ifndef NATIVE_ACTIVITY_FILE_H
#define NATIVE_ACTIVITY_FILE_H

#include <string>
#include <android/asset_manager_jni.h>

class File {

public:
    File(const char *fileName, AAssetManager *assetManager);

    virtual ~File();

    void *buff() const;

    std::string fileName() const { return _fileName; }

    long length() const { return _length; }

private:
    std::string _fileName;
    void *_buff;
    long _length;
};

#endif //NATIVE_ACTIVITY_FILE_H
