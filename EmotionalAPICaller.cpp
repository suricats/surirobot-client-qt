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
    camera = new QCamera();
    captureTimer = new QTimer();
    std::cout << "Hi";
    recorder = new QCameraImageCapture(camera);
    std::cout << "Hey";
    recorder->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    //Set the capture timer (every 0,5 seconds)
    captureTimer->setInterval(500);
    QObject::connect(captureTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    QObject::connect(recorder, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(imageCaptured(int, const QImage&)));
    imageVec.clear();

}

EmotionalAPICaller::~EmotionalAPICaller() {
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
        std::cout << "EmoAPI : " << reply->readAll().toStdString() << std::endl;
        QString message = jsonObject["scores"].toString("No emotion detected");
        std::cout << "Message : " << message.toStdString() << std::endl;
        emit messageChanged(message);


    }
    reply->deleteLater();
}

void EmotionalAPICaller::captureImage() {
    recorder->capture();
}

void EmotionalAPICaller::imageCaptured(int id, const QImage& preview) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    preview.save(&buffer, "BMP");
    QByteArray arr = qCompress(buffer.buffer(), 5);
    QString a = arr.toBase64();
    imageVec.push_back(a);
    if (imageVec.size() > 5) emit sendRequest();
}

void EmotionalAPICaller::start() {
    currentThread->start();
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start();
    captureTimer->start();

}

void EmotionalAPICaller::sendRequest() {

    QUrl serviceURL("https://emotional.api.surirobot.net/");

    QJsonObject jsonObject;
    QJsonArray pictures;
    for (QString str : imageVec) {
        pictures.append(QJsonValue(str));
    }
    //jsonObject["pictures"] = QJsonValue(imageVec.at(0));
    imageVec.clear();
    QJsonDocument jsonData(jsonObject);
    QByteArray data = jsonData.toJson();
    QNetworkRequest request(serviceURL);
    std::cout << "Request sent to EmotionalAPI" << data.toStdString() << std::endl;
    //request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    //request.setRawHeader("User-Agent", "My app name v0.1");
    //request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    //request.setRawHeader("Content-Length", postDataSize);
    networkManager->post(request, data);
}

