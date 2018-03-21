
#include "EmotionalAPICaller.hpp"
#include "src/controller/faceManager.hpp"

EmotionalAPICaller::EmotionalAPICaller(QString text) :
APICaller(text) {
    if (!cap.open(-1)) std::cerr << "Error - No camera found" << std::endl;
    captureTimer = new QTimer();
    requestTimer = new QTimer();
    //Set the capture timer (every 3 seconds)
    captureTimer->setInterval(200);
    requestTimer->setInterval(EMOTIONAL_DELAY);
    QObject::connect(captureTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    QObject::connect(requestTimer, SIGNAL(timeout()), this, SLOT(sendRequest()));
}

EmotionalAPICaller::~EmotionalAPICaller() {
    captureTimer->stop();
    requestTimer->stop();
    stop();
    delete captureTimer;
}

void EmotionalAPICaller::receiveReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error " << reply->error() << std::endl;
        std::cerr << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        QJsonArray tmpAr = jsonObject["facial"].toArray();
        QString message = "Emotions : ";
        for(QJsonValue val : tmpAr)
        {
            message += val.toObject()["emotion"].toString("?");
            message += ",";
        }
        emit newReply(message);


    }
    isBusy = false;
    reply->deleteLater();
}

void EmotionalAPICaller::captureImage() {
    if (!isBusy) {
        cap >> currentFrame;
        cv::resize(currentFrame, currentFrame, cv::Size(EMOTIONAL_IMAGE_SIZE, EMOTIONAL_IMAGE_SIZE));
        std::string a = "Camera n°1";
        cv::imshow(a, currentFrame);
        
    }
}

void EmotionalAPICaller::start() const {
    APICaller::start();
    captureTimer->start();
    requestTimer->start();
    
}

void EmotionalAPICaller::sendRequest(QString text) {
    if (!isBusy) {
        isBusy = true;
        //Get base64 string from cv::mat
        std::string ext = "jpeg";
        std::vector<uint8_t> buffer;
        cv::imencode("." + ext, currentFrame, buffer);
        QByteArray byteArray = QByteArray::fromRawData((const char*) buffer.data(), buffer.size());
        QString base64Image(byteArray.toBase64());
        
        //Prepare request
        QJsonObject jsonObject;
        jsonObject["pictures"] = base64Image;
        QJsonDocument jsonData(jsonObject);
        QByteArray data = jsonData.toJson();
        QNetworkRequest request(url);
        //std::cout << "Sended to Emotional API : " << data.toStdString().substr(0,30) << "..." << std::endl;
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        networkManager->post(request, data);
    }
}

