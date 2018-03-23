

#ifndef TTSAPICALLER_HPP
#define TTSAPICALLER_HPP

#include "APICaller.hpp"
#include "FileDownloader.hpp"

//Model headers
#include "../sound/MusicPlayer.hpp"

class TTSAPICaller : public APICaller{
    Q_OBJECT
private:
    FileDownloader* fileDownloader;
    MusicPlayer* musicPlayer;
public:
    void readAudio(std::string filename);
    explicit TTSAPICaller(QString text);
    ~TTSAPICaller();
    void start() const override;
    void stop() const override;
public slots:
    void sendRequest(QString text) override;
    void receiveReply(QNetworkReply* reply) override;
private slots:
    void downloadFinished(QByteArray file);
signals:
    void interruptSound();
    void download(QString);
    void playSound(QString);
};

#endif /* TTSAPICALLER_HPP */

