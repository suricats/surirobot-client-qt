
#include "ConverseAPICaller.hpp"
#include "src/conf.hpp"


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
        
        QString message = jsonObject["answerText"].toString("Can't find message.");
        std::cout << "Received from Converse API : " << message.toStdString() << std::endl;
        emit newReply(message);

    }
    reply->deleteLater();
}

void ConverseAPICaller::sendRequest(QString filepath) {

    if (!isBusy) {

        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        //Language
        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"language\""));
        textPart.setBody(DEFAULT_LANGUAGE);
        //Audio
        QHttpPart audioPart;
        audioPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"audio\"; filename=\"audio.wav\""));
        audioPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("audio/x-wav"));
        QFile *file = new QFile(filepath);
        file->open(QIODevice::ReadOnly);
        audioPart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        multiPart->append(audioPart);
        multiPart->append(textPart);
        QNetworkRequest request(url);
        std::cout << "Sended to Converse API : " << "File - " << file->fileName().toStdString() << " - " << file->size()/1000 << "Ko" << std::endl;
        isBusy = true;
        QNetworkReply *reply = networkManager->post(request, multiPart);
        multiPart->setParent(reply);

    }

}

