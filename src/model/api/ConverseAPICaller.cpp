
#include "ConverseAPICaller.hpp"
#include "src/conf.hpp"

ConverseAPICaller::ConverseAPICaller(QString text) :
APICaller(text) {
    fileDownloader = new QNetworkAccessManager();
    fileDownloader->moveToThread(currentThread);
    QObject::connect(fileDownloader, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    QObject::connect(this, SIGNAL(download(QString)), this, SLOT(startDownload(QString)));
}

ConverseAPICaller::~ConverseAPICaller() {
}


void ConverseAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
    //audioPlayer->stop();
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error  " << reply->error() << " : " << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();

        QString message = jsonObject["answerText"].toString("Can't find message.");
        QString url = jsonObject["answerAudioLink"].toString("");
        std::cout << "Received from Converse API : " << message.toStdString() << std::endl;
        emit newReply(message);
        //Play the sound
        std::cout << "Downloading the sound : " << url.toStdString() << std::endl;
        emit download(url);


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
        std::cout << "Sended to Converse API : " << "File - " << file->fileName().toStdString() << " - " << file->size() / 1000 << "Ko" << std::endl;
        isBusy = true;
        QNetworkReply *reply = networkManager->post(request, multiPart);
        multiPart->setParent(reply);

    }

}

void ConverseAPICaller::startDownload(QString url) {
    QUrl parsedUrl = url;
    QNetworkRequest request(parsedUrl);
    fileDownloader->get(request);
    isBusy = true;
}

void ConverseAPICaller::downloadFinished(QNetworkReply* reply) {

    std::cout << "Download finished." << std::endl;
    //generate filename
    uuid_t id;
    uuid_generate(id);
    char *string = new char[30];
    uuid_unparse(id, string);
    std::string uuid = string;
    std::string filename = TMP_DIR + uuid + ".wav";
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Could not create file : " << filename << std::endl;
    }
    file.write(reply->readAll());
    std::cout << "Sound file generated at : " << filename << std::endl;
    file.close();
    
    ///Play the audio
    
    this->readAudio(filename);
    isBusy = false;
    reply->deleteLater();
}

void ConverseAPICaller::readAudio(std::string filename)
{
    
    std::stringstream ss;
    ss << "exec aplay " << filename;
    system(ss.str().c_str());
}