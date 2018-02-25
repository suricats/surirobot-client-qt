#ifndef EMOTIONALAPICALLER_HPP
#define EMOTIONALAPICALLER_HPP

#include "APICaller.hpp"
#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QCamera>

class EmotionalAPICaller : public APICaller {
    Q_OBJECT
private:
    QCamera* camera;
    QCameraImageCapture* recorder;
    QTimer* captureTimer;
    std::vector<QString> imageVec;
public:
    explicit EmotionalAPICaller(QString text);
    virtual ~EmotionalAPICaller();
    void start() const override;
public slots:
    void sendRequest(QString text = "") override;
    void receiveReply(QNetworkReply* reply) override;
    void captureImage();
    void imageCaptured(int id, const QImage& preview);

};

#endif /* EMOTIONALAPICALLER_HPP */

