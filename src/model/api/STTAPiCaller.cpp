#include "STTAPiCaller.hpp"

STTAPiCaller::STTAPiCaller(QString text) :
APICaller(text) {
    
}

STTAPiCaller::~STTAPiCaller() {
    stop();
}

void STTAPiCaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
    //audioPlayer->stop();
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error  " << reply->error() << " : " << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();

    }
    reply->deleteLater();
}

void STTAPiCaller::sendRequest(QString filepath) {


}
