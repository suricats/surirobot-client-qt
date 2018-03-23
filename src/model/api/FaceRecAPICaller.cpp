
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
void FaceRecAPICaller::sendLog(bool val)
{
    std::stringstream ss;
    std::string vals;
    if(val)vals="true";
    else vals="false";
    ss << "curl -d '{\"value\":\"" << vals << "\"}' -H \"Content-Type: application/json\" -X POST http://localhost:5000/logs/recognize";
    std::cout << ss.str() << std::endl;
    system(ss.str().c_str());
    /*
    if (!isBusy) {
        isBusy = true;
        //Prepare request
        QJsonObject jsonObject;
        jsonObject["value"] = val;
        
        QJsonDocument jsonData(jsonObject);
        QByteArray data = jsonData.toJson();
        
        QString s(url.toString()+"/logs/recognize/");
        QUrl nUrl(s);
        std::cout << nUrl.toString().toStdString() << std::endl;
        QNetworkRequest request(nUrl);
        request.setAttribute(QNetworkRequest::RedirectionTargetAttribute, true);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        networkManager->post(request, data);
    }
     */
}

