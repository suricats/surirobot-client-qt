#include "APICaller.hpp"

APICaller::APICaller()
{
    this->url = "https://www.google.fr";
    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveReply(QNetworkReply*)));
    currentThread = new QThread;
    moveToThread(currentThread);
}
APICaller::APICaller(QString url) {
    this->url = url;
    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveReply(QNetworkReply*)));
    currentThread = new QThread;
    moveToThread(currentThread);
}

APICaller::~APICaller() {
    currentThread->quit();
    delete currentThread;
    delete networkManager;
}
void APICaller::start() const{
    currentThread->start();
    
}
void APICaller::stop()
{
    currentThread->quit();
}
