
#include "ConverseAPICaller.hpp"

ConverseAPICaller::ConverseAPICaller(QString text) :
APICaller(text) {

}

ConverseAPICaller::~ConverseAPICaller() {
}

void ConverseAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error  " << reply->error() << " : " << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        std::cout << "Received from Converse API : " << reply->readAll().toStdString() << std::endl;
        QString message = jsonObject["answerText"].toString("Can't find message.");
        emit newReply(message);

    }
    reply->deleteLater();
}

void ConverseAPICaller::sendRequest(QString filepath) {

    if (!isBusy) {



        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        //Language
        /*
        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"language\""));
        textPart.setBody("fr");
        */
        //Audio
        QHttpPart audioPart;
        audioPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("audio/x-wav"));
        audioPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"audio\""));
        QFile *file = new QFile("tmp/bd212fcc-c7e0-4092-9e90-5f628486307e.wav");
        std::cout << "File size :" << file->size() << std::endl;
        file->open(QIODevice::ReadOnly);
        audioPart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        multiPart->append(audioPart);
        //multiPart->append(textPart);


        
        QNetworkRequest request(url);
        std::cout << "Sended to Converse API : " << "..." << std::endl;

        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data; boundary=723690991551375881941828858"));
        //request.setRawHeader("User-Agent", "My app name v0.1");
        //request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
        //request.setRawHeader("Content-Length", postDataSize);
        isBusy = true;
        QNetworkReply *reply = networkManager->post(request, multiPart);
        multiPart->setParent(reply);

    }

}

