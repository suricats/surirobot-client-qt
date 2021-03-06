
#ifndef SPEECHRECORDING_HPP
#define SPEECHRECORDING_HPP

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <iomanip>
#include <vector>
#include <sndfile.h>

#include "../../conf.hpp"
#include <uuid/uuid.h>
//Library to handle Audio
#include <AL/al.h>
#include <AL/alc.h>


#include <QString>
#include <QObject>
#include <QThread>

#define DEFAULT_PLANIFIED_SEC 4

class SpeechRecording : public QObject {
    Q_OBJECT
        private:

            //Devices to handle microphone
            ALCdevice *Device = NULL;
    ALCdevice *CaptureDevice = NULL;
    //List of all devices
    std::vector<std::string> Devices;
    // We will stock our samples in vector of Int16
    std::vector<ALshort> Samples;

public:
    QThread* currentThread;
    int audioPeriod;
    SpeechRecording();
    ~SpeechRecording();
    void start();

    ////////////////////////////////////////////////////////////
    /// Initialise OpenAL (open device and create context
    ///
    /// \param DeviceName : name of the device (NULL for default device)
    ///
    /// \return True if all went well, False if something went wrong
    ///
    ////////////////////////////////////////////////////////////
    bool InitOpenAL(const char* DeviceName = NULL);

    ////////////////////////////////////////////////////////////
    /// Initialize the audio capture
    ///
    /// \param DeviceName : name of the device (NULL for default device)
    ///
    /// \return True if all went well, False if something went wrong
    ///
    ////////////////////////////////////////////////////////////
    bool InitCapture(const char* DeviceName = NULL);

    ////////////////////////////////////////////////////////////
    /// Close OpenAL
    ///
    ////////////////////////////////////////////////////////////
    void ShutdownOpenAL();

    ////////////////////////////////////////////////////////////
    /// Get the list of devices connected
    ///
    /// \param Devices : vector of string to fill
    ///
    ////////////////////////////////////////////////////////////
    void GetCaptureDevices(std::vector<std::string>& Devices);

    ////////////////////////////////////////////////////////////
    /// Convert and save a sample tab into a wav file
    ///
    /// \param Filename : name of the file wav
    /// \param Samples :  vector of samples
    ///
    ////////////////////////////////////////////////////////////
    void SaveSound(const std::string& Filename, const std::vector<ALshort>& Samples);


public slots:
    int recordXSeconds(float second = 6);
    int recordPSeconds();
    void recordInBuffer(float second = 1);
    int saveBuffer();
signals:
    void newSoundCreated(QString text);
    void isRecording(bool val);

private:
    bool isInit;
};

#endif /* SPEECHRECORDING_HPP */


