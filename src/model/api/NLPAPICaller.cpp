
#include "NLPAPICaller.hpp"
#include "src/conf.hpp"

NLPAPICaller::NLPAPICaller(QString text) :
APICaller(text) {

}

NLPAPICaller::~NLPAPICaller() {
    stop();
}

void NLPAPICaller::receiveReply(QNetworkReply* reply) {
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

void NLPAPICaller::sendRequest(QString text) {
    if (text != "") {
        
        //Create the json request
        QJsonObject jsonObject;
        jsonObject["text"] = text;
        jsonObject["language"] = DEFAULT_LANGUAGE;
        QJsonDocument jsonData(jsonObject);
        QByteArray data = jsonData.toJson();
        QNetworkRequest request(url);
        std::cout << "Sended to NLP API : " << data.toStdString() << std::endl;
        //request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        isBusy=true;
        networkManager->post(request, data);
    }

}

