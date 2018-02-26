
#include "EmotionalAPICaller.hpp"

EmotionalAPICaller::EmotionalAPICaller(QString text) :
APICaller(text) {
    if (!cap.open(-1)) std::cerr << "Error - No camera found" << std::endl;
    captureTimer = new QTimer();
    //Set the capture timer (every 0,5 seconds)
    captureTimer->setInterval(100);
    QObject::connect(captureTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
    imageVec.clear();

}

EmotionalAPICaller::~EmotionalAPICaller() {
    captureTimer->stop();
    delete captureTimer;
    imageVec.clear();
}

void EmotionalAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
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

    cv::Mat frame;
    cap >> frame;
    cv::Mat dst;
    cv::resize(frame, dst, cv::Size(150, 150));
    std::string ext = "jpeg";
    std::string a = "Camera n°" + std::to_string(imageVec.size());
    cv::imshow(a, dst);
    std::vector<uint8_t> buffer;
    cv::imencode("." + ext, dst, buffer);
    QByteArray byteArray = QByteArray::fromRawData((const char*) buffer.data(), buffer.size());
    QString base64Image(byteArray.toBase64());

    std::stringstream ss;
    ss << "data:image/" << ext << ";base64,";
    std::string s = ss.str() + base64Image.toStdString();
    base64Image = QString::fromStdString(s);
    imageVec.push_back(base64Image);
    if (imageVec.size() > 10) emit sendRequest();



}

/*
 
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
 */
void EmotionalAPICaller::start() const {
    APICaller::start();

    captureTimer->start();

}

void EmotionalAPICaller::sendRequest(QString text) {
    if (!isBusy) {
        QJsonObject jsonObject;
        QJsonArray pictures;
        for (QString str : imageVec) {
            pictures.append(QJsonValue(str));
        }
        jsonObject["pictures"] = pictures;
        QJsonDocument jsonData(jsonObject);
        imageVec.clear();
        QByteArray data = jsonData.toJson();
        QNetworkRequest request(url);
        std::cout << "Sended to Emotional API : " << "..."/*data.toStdString()*/ << std::endl;
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        isBusy = true;
        networkManager->post(request, data);
    }

}

