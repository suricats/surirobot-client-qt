#include "generalManager.hpp"

generalManager* generalManager::instance = NULL;

void generalManager::deleteInstance() {
    delete instance;
    instance = NULL;
}

generalManager* generalManager::getInstance() {
    if (!generalManager::instance) {
        instance = new generalManager();
    }
    return instance;
}

generalManager::generalManager() {

}

generalManager::~generalManager() {

}

void generalManager::deleteAll() {
    //Stop the controllers
    faceManager::getInstance()->stop();
    converseManager::getInstance()->stop();
    //Delete the controllers
    faceManager::deleteInstance();
    converseManager::deleteInstance();
    deleteTemporaryFiles();

}

void generalManager::deleteTemporaryFiles() {
    QString path = TMP_DIR;
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);

    foreach(QString dirFile, dir.entryList()) {
        dir.remove(dirFile);
    }
}
