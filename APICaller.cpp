/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   APICaller.cpp
 * Author: Alain BERRIER
 * 
 * Created on 8 février 2018, 20:40
 */


#include "APICaller.h"

APICaller::APICaller(QObject *parent) :
QObject(parent) {
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveReply(QNetworkReply*)));
}

void APICaller::receiveReply(QNetworkReply* reply) {
    std::cout << "Reply received" << std::endl;
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error " << reply->error() << std::endl;
        std::cerr << reply->readAll().toStdString() << std::endl;
        nam->clearAccessCache();
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


    }


    reply->deleteLater();
}

void APICaller::set(QThread* thread) {
    //QObject::connect(thread, SIGNAL(started()), this, SLOT(sendRequest()));
    moveToThread(thread);
}

void APICaller::sendRequest(QString text) {

    // Time for building your request
    QUrl serviceURL("https://nlp.api.surirobot.net/getanswer");

    /*
     * SEND FORM-DATA
    QUrlQuery postData;
    postData.addQueryItem("username", "wesha !");
    postData.addQueryItem("email", "a");
    postData.addQueryItem("password", "1234");
    
    //postData.addQueryItem("lang","fr");
    serviceURL.setQuery(postData.query());
     */

    QJsonObject jsonObject;
    jsonObject["text"] = text;
    jsonObject["language"] = "fr";
    QJsonDocument jsonData(jsonObject);
    QByteArray data = jsonData.toJson();
    //std::cout << "Request : " << std::endl << data.toStdString() << std::endl;
    QNetworkRequest request(serviceURL);

    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    //request.setRawHeader("User-Agent", "My app name v0.1");
    //request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    //request.setRawHeader("Content-Length", postDataSize);
    nam->post(request, data);
}

