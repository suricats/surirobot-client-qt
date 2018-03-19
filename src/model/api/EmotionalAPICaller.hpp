#ifndef EMOTIONALAPICALLER_HPP
#define EMOTIONALAPICALLER_HPP

#include "APICaller.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class EmotionalAPICaller : public APICaller {
    Q_OBJECT
private:
    QTimer* captureTimer;
    cv::VideoCapture cap;
    
public:
    int cpts;
    explicit EmotionalAPICaller(QString text);
    virtual ~EmotionalAPICaller();
    void start() const override;
public slots:
    void sendRequest(QString text = "") override;
    void receiveReply(QNetworkReply* reply) override;
    void captureImage();
    //void imageCaptured(int id, const QImage& preview);

};

#endif /* EMOTIONALAPICALLER_HPP */

