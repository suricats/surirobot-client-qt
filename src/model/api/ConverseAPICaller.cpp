
#include "ConverseAPICaller.hpp"
#include "src/model/sound/SpeechRecording.hpp"

ConverseAPICaller::ConverseAPICaller(QString text) :
APICaller(text) {
    intentMode = false;
    fileDownloader = new FileDownloader();
    musicPlayer = MusicPlayer::getInstance();
    QObject::connect(fileDownloader, SIGNAL(newFile(QByteArray)), this, SLOT(downloadFinished(QByteArray)));
    QObject::connect(this, SIGNAL(download(QString)), fileDownloader, SLOT(sendRequest(QString)));
    QObject::connect(this, SIGNAL(playSound(QString)), musicPlayer, SLOT(playSound(QString)));
    QObject::connect(this, SIGNAL(interruptSound()), musicPlayer, SLOT(interruptRequest()));
}

ConverseAPICaller::~ConverseAPICaller() {
    stop();
}

void ConverseAPICaller::receiveReply(QNetworkReply* reply) {
    isBusy = false;
    QByteArray buffer(reply->readAll());
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error  " << reply->error() << " : " << buffer.toStdString() << std::endl;
        networkManager->clearAccessCache();
    }
    QJsonObject jsonObject = QJsonDocument::fromJson(buffer).object();
    if (intentMode) {
        QString intent = jsonObject["intent"].toString();
        if (intent == "say-yes") {
            std::cout << "OUI INTENT" << std::endl;
            emit newIntent(State::STATE_CONFIRMATION_YES, intent.toUtf8());
        }
        if (intent == "say-no") {
            std::cout << "OUI INTENT" << std::endl;
            emit newIntent(State::STATE_CONFIRMATION_NO, intent.toUtf8());
        }


    } else {
        QString message = jsonObject["answerText"].toString();
        QString url = jsonObject["answerAudioLink"].toString();
        if (!message.isEmpty()) {

            std::cout << "Received from Converse API : " << message.toStdString() << std::endl;
            emit newReply(message);
        }
        else emit newReply("Je ne me sens pas bien... [ERROR Conv : Field message needed but doesn't exist.]");
        if(!url.isEmpty()){
            std::cout << "Downloading the sound : " << url.toStdString() << std::endl;
            emit download(url);
        }

    }


    reply->deleteLater();
}

void ConverseAPICaller::sendRequest(QString filepath) {

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

    //Id
    QHttpPart idPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"userId\""));
    textPart.setBody("1");
    multiPart->append(audioPart);
    multiPart->append(textPart);
    multiPart->append(idPart);
    QNetworkRequest request(url);
    std::cout << "Sended to Converse API : " << "File - " << file->fileName().toStdString() << " - " << file->size() / 1000 << "Ko" << std::endl;
    isBusy = true;
    QNetworkReply *reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply);



}

void ConverseAPICaller::start() const {
    APICaller::start();
    fileDownloader->start();
    musicPlayer->start();

}

void ConverseAPICaller::stop() const {
    fileDownloader->stop();
    musicPlayer->currentThread->quit();
    APICaller::stop();
}

void ConverseAPICaller::downloadFinished(QByteArray data) {

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
    //Restart the audioplayer
    emit interruptSound();
    emit playSound(QString::fromStdString(filename));

}

void ConverseAPICaller::readAudio(std::string filename) {
    //std::stringstream ss;
    //ss << "exec aplay " << filename;
    //system(ss.str().c_str());



}
