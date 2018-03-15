
#include "EmotionalAPICaller.hpp"
#include "src/controller/faceManager.hpp"

EmotionalAPICaller::EmotionalAPICaller(QString text) :
APICaller(text) {
    if (!cap.open(-1)) std::cerr << "Error - No camera found" << std::endl;
    captureTimer = new QTimer();
    //Set the capture timer (every 3 seconds)
    captureTimer->setInterval(EMOTIONAL_DELAY);
    QObject::connect(captureTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
}

EmotionalAPICaller::~EmotionalAPICaller() {
    captureTimer->stop();
    stop();
    delete captureTimer;
}

void EmotionalAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
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
        //std::cout << "EmoAPI : " << QJsonDocument::fromJson(reply->readAll()).toBinaryData().toStdString() << std::endl;
        //QString message = jsonObject["facial"].toString("No emotion detected");
        emit newReply(message);


    }
    reply->deleteLater();
}

void EmotionalAPICaller::captureImage() {
    if (!isBusy) {
        cv::Mat frame;
        cap >> frame;
        cv::Mat dst;
        cv::resize(frame, dst, cv::Size(EMOTIONAL_IMAGE_SIZE, EMOTIONAL_IMAGE_SIZE));
        std::string ext = "jpeg";
        std::string a = "Camera n°1";
        cv::imshow(a, dst);
        std::vector<uint8_t> buffer;
        cv::imencode("." + ext, dst, buffer);
        QByteArray byteArray = QByteArray::fromRawData((const char*) buffer.data(), buffer.size());
        QString base64Image(byteArray.toBase64());

        //std::stringstream ss;
        //ss << "data:image/" << ext << ";base64";
        //std::string s = ss.str() + base64Image.toStdString();
        //base64Image = QString::fromStdString(s);
        sendRequest(base64Image);
    }
}

void EmotionalAPICaller::start() const {
    APICaller::start();
    captureTimer->start();
    
}

void EmotionalAPICaller::sendRequest(QString text) {
    if (!isBusy) {
        isBusy = true;
        QJsonObject jsonObject;
        jsonObject["pictures"] = text;
        QJsonDocument jsonData(jsonObject);
        QByteArray data = jsonData.toJson();
        QNetworkRequest request(url);
        std::cout << "Sended to Emotional API : " << "..." /*<< data.toStdString()*/ << std::endl;
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        networkManager->post(request, data);
    }

}

