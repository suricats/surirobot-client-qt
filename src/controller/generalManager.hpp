
#ifndef GENERALMANAGER_HPP
#define GENERALMANAGER_HPP

//Controller headers
#include "converseManager.hpp"
#include "faceManager.hpp"

class generalManager : public QObject {
    Q_OBJECT
public:
    //Singleton
    static generalManager* getInstance();
    static void deleteInstance();
    //Singleton security
    generalManager(generalManager const&) = delete;
    void operator=(generalManager const&) = delete;

    ~generalManager();

private:
    generalManager();
    static generalManager* instance;

    void deleteTemporaryFiles();

public slots:
    void deleteAll();
    

};

#endif /* GENERALMANAGER_HPP */

