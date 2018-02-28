
#ifndef NLPAPICALLER_HPP
#define NLPAPICALLER_HPP

#include "APICaller.hpp"

class NLPAPICaller : public APICaller {
    Q_OBJECT
public:
    explicit NLPAPICaller(QString text);
    ~NLPAPICaller();
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;

};


#endif /* NLPAPICALLER_HPP */

