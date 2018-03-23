
#include "FaceRecAPICaller.hpp"


FaceRecAPICaller::FaceRecAPICaller(QString text) :
APICaller(text) {
    
}

FaceRecAPICaller::~FaceRecAPICaller() {
    stop();
}

void FaceRecAPICaller::receiveReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error " << reply->error() << std::endl;
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
void FaceRecAPICaller::sendLog(QString id,bool val)
{
    if (!isBusy) {
        isBusy = true;
        std::cout << "Salut" << std::endl;
        //Prepare request
        QJsonObject jsonObject;
        jsonObject["value"] = val;
        
        QJsonDocument jsonData(jsonObject);
        QByteArray data = jsonData.toJson();
        
        QString s(url.toString()+"/logs/recognize/"+id);
        QUrl nUrl(s);
        QNetworkRequest request(nUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        networkManager->post(request, data);
    }
}

