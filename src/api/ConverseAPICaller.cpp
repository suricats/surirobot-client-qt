
#include "ConverseAPICaller.hpp"

ConverseAPICaller::ConverseAPICaller(QString text) :
APICaller(text) {

}

ConverseAPICaller::~ConverseAPICaller() {
}

void ConverseAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy=false;
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error  " << reply->error() << " : " << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        std::cout << "Received from Converse API : " << reply->readAll().toStdString() << std::endl;
        QJsonArray messagesJson = jsonObject["results"].toObject()["messages"].toArray();
        if (!messagesJson.isEmpty()) {
            QJsonValueRef queryValue = messagesJson[0].toObject()["content"];
            if (!queryValue.isNull() && !queryValue.isUndefined()) {
                QString message = queryValue.toString();
                emit newReply(message);
            }
        } else emit newReply(QString("Can't find message."));

    }
    reply->deleteLater();
}

void ConverseAPICaller::sendRequest(QString text) {
    /*
    SEND FORM-DATA
    QUrlQuery postData;
    postData.addQueryItem("username", "wesha !");
    postData.addQueryItem("email", "a");
    postData.addQueryItem("password", "1234");
    
    //postData.addQueryItem("lang","fr");
    serviceURL.setQuery(postData.query());
    */
    if (text != "" && !isBusy) {
        
        //Create the json request
        QJsonObject jsonObject;
        jsonObject["text"] = text;
        jsonObject["language"] = "fr";
        QJsonDocument jsonData(jsonObject);
        QByteArray data = jsonData.toJson();
        QNetworkRequest request(url);
        std::cout << "Sended to Converse API : " << data.toStdString() << std::endl;
        //request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        //request.setRawHeader("User-Agent", "My app name v0.1");
        //request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
        //request.setRawHeader("Content-Length", postDataSize);
        isBusy=true;
        networkManager->post(request, data);
    }

}

