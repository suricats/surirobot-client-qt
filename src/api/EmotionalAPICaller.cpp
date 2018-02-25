
#include "EmotionalAPICaller.hpp"

EmotionalAPICaller::EmotionalAPICaller(QString text) :
APICaller(text) {
    if(QCameraInfo::availableCameras().count() <= 0) camera = new QCamera();
    else camera = new QCamera(QCameraInfo::availableCameras().first());
    captureTimer = new QTimer();
    recorder = new QCameraImageCapture(camera);
    recorder->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    //Set the capture timer (every 0,5 seconds)
    captureTimer->setInterval(500);
    QObject::connect(captureTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    QObject::connect(recorder, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(imageCaptured(int, const QImage&)));
    imageVec.clear();

}

EmotionalAPICaller::~EmotionalAPICaller() {
    delete camera;
    captureTimer->stop();
    delete captureTimer;
    imageVec.clear();
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
        emit newReply(message);


    }
    reply->deleteLater();
}

void EmotionalAPICaller::captureImage() {
    recorder->capture();
    camera->unlock();
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

void EmotionalAPICaller::start() const {
    APICaller::start();
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start();
    camera->searchAndLock();
    captureTimer->start();

}

void EmotionalAPICaller::sendRequest(QString text) {
    QJsonObject jsonObject;
    QJsonArray pictures;
    for (QString str : imageVec) {
        pictures.append(QJsonValue(str));
    }
    imageVec.clear();
    QJsonDocument jsonData(jsonObject);
    QByteArray data = jsonData.toJson();
    QNetworkRequest request(url);
    std::cout << "Sended to Emotional API : " << data.toStdString() << std::endl;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    
    networkManager->post(request, data);
}

