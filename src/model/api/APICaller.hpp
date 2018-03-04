
#ifndef APICALLER_HPP
#define APICALLER_HPP

#include <QtNetwork>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QThread>
#include <QString>
#include <QByteArray>
#include <iostream>

class APICaller : public QObject {
    Q_OBJECT
public:
    APICaller();
    APICaller(QString url);
    virtual ~APICaller();
    bool isBusy;
    virtual void start() const;
    void stop();
protected:
    QUrl url;
    QNetworkAccessManager* networkManager;
    QThread* currentThread;
public slots:
    virtual void sendRequest(QString text = "") = 0;
    virtual void receiveReply(QNetworkReply* reply) = 0;
signals:
    void newReply(QString text);

};

#endif /* APICALLER_HPP */

