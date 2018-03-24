
#include "FaceRecAPICaller.hpp"

FaceRecAPICaller::FaceRecAPICaller(QString text) :
APICaller(text) {

}

FaceRecAPICaller::~FaceRecAPICaller() {
    stop();
}

void FaceRecAPICaller::receiveReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error FaceRec : " << reply->error() << std::endl;
        std::cerr << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QString message = reply->readAll();
        std::cout << "FaceRecAPI : " << message.toStdString() << std::endl;
        emit newReply(message);
    }
    isBusy = false;
    reply->deleteLater();
}

void FaceRecAPICaller::sendRequest(QString text) {
    
}

void FaceRecAPICaller::sendLog(bool val) {
    
    //Prepare request
    QJsonObject jsonObject;
    jsonObject["value"] = val;
    QJsonDocument jsonData(jsonObject);
    QByteArray data = jsonData.toJson();
    QString s("http://" + url.toString() + "/logs/recognize");
    QUrl nUrl(s);
    QNetworkRequest request(nUrl);
    request.setAttribute(QNetworkRequest::RedirectionTargetAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    networkManager->post(request, data);
}

