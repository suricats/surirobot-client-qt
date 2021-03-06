
#ifndef FACERECAPICALLER_HPP
#define FACERECAPICALLER_HPP

#include "APICaller.hpp"
#include <sstream>
#include <string>
#include <vector>

#include <QNetworkRequest>
class FaceRecAPICaller : public APICaller {
    Q_OBJECT
private:
    
public:
    explicit FaceRecAPICaller(QString text);
    virtual ~FaceRecAPICaller();
public slots:
    void sendRequest(QString text = "") override;
    void receiveReply(QNetworkReply* reply) override;
    void sendLog(bool val);

};


#endif /* FACERECAPICALLER_HPP */

