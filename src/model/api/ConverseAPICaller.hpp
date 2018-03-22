#ifndef CONVERSEAPICALLER_HPP
#define CONVERSEAPICALLER_HPP

#include "APICaller.hpp"
#include "FileDownloader.hpp"
#include <sstream>
#include <string>
#include <algorithm>

#include <uuid/uuid.h>

//Model headers
#include "../sound/MusicPlayer.hpp"
#include "../../conf.hpp"

class ConverseAPICaller : public APICaller {
    Q_OBJECT
private:
    FileDownloader* fileDownloader;
    MusicPlayer* musicPlayer;
public:
    void readAudio(std::string filename);
    explicit ConverseAPICaller(QString text);
    ~ConverseAPICaller();
    void start() const override;
    void stop() const override;
    bool intentMode;
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;
    //void updateUsername(QString id,QString username);
private slots:
    void downloadFinished(QByteArray file);
signals:
    void interruptSound();
    void download(QString);
    void playSound(QString);
    void newIntent(State,QByteArray);



};

#endif /* CONVERSEAPICALLER_HPP */

