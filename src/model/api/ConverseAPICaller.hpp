#ifndef CONVERSEAPICALLER_HPP
#define CONVERSEAPICALLER_HPP

#include "APICaller.hpp"
#include <sstream>
#include <string>
#include <uuid/uuid.h>


class ConverseAPICaller : public APICaller {
    Q_OBJECT
private:
    QNetworkAccessManager* fileDownloader;
    
public:
    void readAudio(std::string filename);
    explicit ConverseAPICaller(QString text);
    ~ConverseAPICaller();
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;

    void startDownload(QString url);
private slots:
    void downloadFinished(QNetworkReply* reply);
signals:
    void download(QString);



};

#endif /* CONVERSEAPICALLER_HPP */

