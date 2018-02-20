/* 
 * File:   APICaller.cpp
 * Author: Alain BERRIER
 * 
 * Created on 8 février 2018, 20:40
 */


#include "EmotionalAPICaller.h"

EmotionalAPICaller::EmotionalAPICaller(QObject *parent) :
QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveReply(QNetworkReply*)));
    currentThread = new QThread;
    moveToThread(currentThread);
}
EmotionalAPICaller::~EmotionalAPICaller()
{
    currentThread->quit();
    delete currentThread;
    delete networkManager;
}
void EmotionalAPICaller::receiveReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error " << reply->error() << std::endl;
        std::cerr << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        std::cout << reply->readAll().toStdString() << std::endl;
        QJsonArray messagesJson = jsonObject["results"].toObject()["messages"].toArray();
        if (!messagesJson.isEmpty()) {
            QJsonValueRef queryValue = messagesJson[0].toObject()["content"];
            if (!queryValue.isNull() && !queryValue.isUndefined()) {
                QString message = queryValue.toString();
                std::cout << "message : " << message.toStdString() << std::endl;
                emit messageChanged(message);
            }
        }
        else emit messageChanged(QString("Can't find message."));

    }
    reply->deleteLater();
}

void EmotionalAPICaller::start() {
    currentThread->start();
    
}

void EmotionalAPICaller::sendRequest(QString text) {

    QUrl serviceURL("https://nlp.api.surirobot.net/getanswer");

    QJsonObject jsonObject;
    QJsonArray pictures;
    pictures.append(QJsonValue(text));
    jsonObject["pictures"] = pictures;
    QJsonDocument jsonData(jsonObject);
    QByteArray data = jsonData.toJson();
    QNetworkRequest request(serviceURL);

    //request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    //request.setRawHeader("User-Agent", "My app name v0.1");
    //request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    //request.setRawHeader("Content-Length", postDataSize);
    networkManager->post(request, data);
}

