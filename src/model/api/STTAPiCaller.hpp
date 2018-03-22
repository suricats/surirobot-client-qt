#ifndef STTAPICALLER_HPP
#define STTAPICALLER_HPP

#include "APICaller.hpp"
#include "../../conf.hpp"

class STTAPiCaller : public APICaller
{
public:
    void readAudio(std::string filename);
    explicit STTAPiCaller(QString text);
    ~STTAPiCaller();
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;


};

#endif /* STTAPICALLER_HPP */

