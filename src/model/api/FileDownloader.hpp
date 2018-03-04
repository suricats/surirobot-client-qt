

#ifndef FILEDOWNLOADER_HPP
#define FILEDOWNLOADER_HPP

#include "APICaller.hpp"

class FileDownloader : public APICaller {
    Q_OBJECT
public:
    FileDownloader();
    virtual ~FileDownloader();
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;
    signals :
    void newFile(QByteArray);
};

#endif /* FILEDOWNLOADER_HPP */

