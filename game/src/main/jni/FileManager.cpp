//
// Created by qwerty on 30.10.16.
//

#include "FileManager.h"

FileManager FileManager::fileManager;

FileManager::FileManager() : assetManager(NULL), initialized(false) { }

void FileManager::init(AAssetManager *assetManager) {
    if (!initialized) {
        this->assetManager = assetManager;
        initialized = true;
    }
}

File *FileManager::getFile(std::string fileName) {

    File **file = files.get(fileName);

    if (file == NULL && assetManager != NULL) {
        File *newFile = new File(fileName.c_str(), assetManager);
        files.put(fileName, newFile);
        return newFile;
    }

    return file == NULL ? NULL : *file;
}

FileManager *FileManager::getInstance() {
    return &fileManager;
}
