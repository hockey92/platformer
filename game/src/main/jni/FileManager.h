//
// Created by qwerty on 30.10.16.
//

#ifndef PLATFORMER_FILEMANAGER_H
#define PLATFORMER_FILEMANAGER_H

#include <android/asset_manager.h>
#include "Map.h"
#include "File.h"

class FileManager {
public:
    void init(AAssetManager *assetManager);

    File *getFile(std::string fileName);

    static FileManager *getInstance();

private:
    AAssetManager *assetManager;

    static FileManager fileManager;

    bool initialized;

    Map<std::string, File *> files;

    FileManager();
};

#endif //PLATFORMER_FILEMANAGER_H
