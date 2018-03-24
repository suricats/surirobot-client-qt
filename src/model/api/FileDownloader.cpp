
#include "FileDownloader.hpp"

FileDownloader::FileDownloader() :
APICaller() {

}

FileDownloader::~FileDownloader() {
    stop();
}

void FileDownloader::receiveReply(QNetworkReply* reply) {
    isBusy = false;
    QByteArray data = reply->readAll();
    emit newFile(data);
    reply->deleteLater();
}

void FileDownloader::sendRequest(QString urlStr) {
    url = QUrl::fromUserInput(urlStr);
    QUrl parsedUrl = url;
    QNetworkRequest request(parsedUrl);
    networkManager->get(request);

}