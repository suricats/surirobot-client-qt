#ifndef CONVERSEAPICALLER_HPP
#define CONVERSEAPICALLER_HPP

#include "APICaller.hpp"

class ConverseAPICaller : public APICaller {
    Q_OBJECT
public:
    explicit ConverseAPICaller(QString text);
    ~ConverseAPICaller();
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;

};

#endif /* CONVERSEAPICALLER_HPP */

