
#include "TTSAPICaller.hpp"


#include "TTSAPICaller.hpp"
#include "src/model/sound/SpeechRecording.hpp"

TTSAPICaller::TTSAPICaller(QString text) :
APICaller(text) {
    fileDownloader = new FileDownloader();
    musicPlayer = MusicPlayer::getInstance();
    QObject::connect(fileDownloader, SIGNAL(newFile(QByteArray)), this, SLOT(downloadFinished(QByteArray)));
    QObject::connect(this, SIGNAL(download(QString)), fileDownloader, SLOT(sendRequest(QString)));
    QObject::connect(this, SIGNAL(playSound(QString)), musicPlayer, SLOT(playSound(QString)));
    QObject::connect(this, SIGNAL(interruptSound()), musicPlayer, SLOT(interruptRequest()));
}

TTSAPICaller::~TTSAPICaller() {
    stop();
}

void TTSAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
    //audioPlayer->stop();
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error  " << reply->error() << " : " << reply->readAll().toStdString() << std::endl;
        networkManager->clearAccessCache();
    } else {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        QString url = jsonObject["downloadLink"].toString("");
        if (url.isEmpty()) newReply("Je ne me sens pas bien... [ERROR TTS : Fields needed don't exist.]");
        else {
            std::cout << "Downloading the sound : " << url.toStdString() << std::endl;
            emit download(url);
        }



    }
    reply->deleteLater();
}

void TTSAPICaller::sendRequest(QString text) {

    isBusy = true;
    //Json request
    QJsonObject jsonObject;
    jsonObject["text"] = text;
    jsonObject["language"] = "fr-FR";

    QJsonDocument jsonData(jsonObject);
    QByteArray data = jsonData.toJson();
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    networkManager->post(request, data);

}

void TTSAPICaller::start() const {
    APICaller::start();
    fileDownloader->start();
    musicPlayer->start();

}

void TTSAPICaller::stop() const {
    fileDownloader->stop();
    musicPlayer->currentThread->quit();
    APICaller::stop();
}

void TTSAPICaller::downloadFinished(QByteArray data) {

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
        return;
    }
    file.write(data);
    std::cout << "Sound file generated at : " << filename << std::endl;
    file.close();

    ///Play the audio
    emit interruptSound();
    emit playSound(QString::fromStdString(filename));

}


