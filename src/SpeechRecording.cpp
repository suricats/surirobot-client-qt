#include "SpeechRecording.hpp"

SpeechRecording::SpeechRecording() {
    currentThread = new QThread;
    moveToThread(currentThread);
    // boolean which represent the 'state' of the user
    isTalking = true;

    /*//thread which will check if the user is talking
     pthread_t threadCheckUser;
     semaph = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 0);
     // Creating thread to handle the person talking
     * if (pthread_create(&threadCheckUser, NULL, thread_IsPersonTalking, (void*)isTalking) != 0)
      {
              std::cout << "error in allocating thread" << std::endl;
              exit(EXIT_FAILURE);
      }*/

    //Initialize openAL with default device
    if (!InitOpenAL(NULL)) {
        std::cout << "Error while initializing OpenAL" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get all devices connected
    GetCaptureDevices(Devices);
    int Choice = 0;
    ///If you have some problem decomment the code here
    /**       std::cout << "Veuillez choisir un device pour la capture :" << std::endl << std::endl;
        for (std::size_t i = 0; i < Devices.size(); ++i)
            std::cout << "[" << i << "] " << Devices[i] << std::endl;
        // the user's choice

        std::cin >> Choice;
        std::cin.ignore(10000, '\n');
     */
    // Initialize capture
    if (!InitCapture(Devices[Choice].c_str())) {
        std::cout << "Error with the microphone... Exit Failure" << std::endl;
        exit(EXIT_FAILURE);
    }
    alcCaptureStart(CaptureDevice);
}

SpeechRecording::~SpeechRecording() {
    // Shutdwown
    alcCaptureCloseDevice(CaptureDevice);
    ShutdownOpenAL();

    //end of program
    ///pthread_join(threadCheckUser, NULL);
    sem_destroy(semaph);
    //std::cout << "End of Speech" << std::endl;
}
void SpeechRecording::start() {
    currentThread->start();
    
}
bool SpeechRecording::InitOpenAL(const char* DeviceName) {
    // Opening device
    Device = alcOpenDevice(DeviceName);
    if (!Device) {
        std::cerr << "Could not open device" << std::endl;
        return false;
    }

    // Context
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (!Context) {
        std::cerr << "Could not create context" << std::endl;
        return false;
    }

    // Context starting
    if (!alcMakeContextCurrent(Context)) {
        std::cerr << "Could not start the audio context" << std::endl;
        return false;
    }

    return true;
}

bool SpeechRecording::InitCapture(const char* DeviceName) {
    // Check If audio captur is supported
    if (alcIsExtensionPresent(Device, "ALC_EXT_CAPTURE") == AL_FALSE) {
        std::cerr << "Audio Capture not supported by the system" << std::endl;
        return false;
    }

    // Opening device
    CaptureDevice = alcCaptureOpenDevice(DeviceName, 22050, AL_FORMAT_MONO16, 22050);
    if (!CaptureDevice) {
        std::cerr << "Could not open capture device" << std::endl;
        return false;
    }

    return true;
}

void SpeechRecording::ShutdownOpenAL() {
    // Retrieve context
    ALCcontext* Context = alcGetCurrentContext();

    // Desactivate the context
    alcMakeContextCurrent(NULL);

    // Suppress context
    alcDestroyContext(Context);

    // Close device
    alcCloseDevice(Device);
}

void SpeechRecording::GetCaptureDevices(std::vector<std::string>& Devices) {
    Devices.clear();

    // Retrieve available devices
    const ALCchar* DeviceList = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);

    if (DeviceList) {
        // retrieve the devices in the returned string
        while (strlen(DeviceList) > 0) {
            Devices.push_back(DeviceList);
            DeviceList += strlen(DeviceList) + 1;
        }
    } else {
        std::cerr << "Could not get a list of connected devices" << std::endl;
    }
}

void SpeechRecording::SaveSound(const std::string& Filename, const std::vector<ALshort>& Samples) {
    // Parametter of file to create
    SF_INFO FileInfos;
    FileInfos.channels = 1;
    FileInfos.samplerate = 44100;
    FileInfos.format = SF_FORMAT_PCM_16 | SF_FORMAT_WAV;

    // Opening file
    SNDFILE* File = sf_open(Filename.c_str(), SFM_WRITE, &FileInfos);
    if (!File) {
        std::cout << "Error with wav file.. Exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Ecriture des échantillons audio
    sf_write_short(File, &Samples[0], Samples.size());

    // Fermeture du fichier
    sf_close(File);
}

void* SpeechRecording::thread_IsPersonTalking(void* isTalking) {
    do {
        //check if person is talking
        //Data signal processing
        // if sound is not important in buffer, then isTalking = false;
        sem_wait(semaph);
    } while ((bool)isTalking);
    std::cout << "End of threadTalking" << std::endl;
    return (void*) NULL;
}

int SpeechRecording::recordXSeconds(float second) {

    ///Here to change second       // 6sec of captur
    time_t Start = time(NULL);
    while (time(NULL) - Start < second) {
        // get the samples
        ALCint SamplesAvailable;
        alcGetIntegerv(CaptureDevice, ALC_CAPTURE_SAMPLES, 1, &SamplesAvailable);

        // read sample and had them to tab
        if (SamplesAvailable > 0) {
            std::size_t Start = Samples.size();
            Samples.resize(Start + SamplesAvailable);
            alcCaptureSamples(CaptureDevice, &Samples[Start], SamplesAvailable);
        }
    }

    //Stop the microphone
    alcCaptureStop(CaptureDevice);
    ALCint SamplesAvailable;
    alcGetIntegerv(CaptureDevice, ALC_CAPTURE_SAMPLES, 1, &SamplesAvailable);
    if (SamplesAvailable > 0) {
        std::size_t Start = Samples.size();
        Samples.resize(Start + SamplesAvailable);
        alcCaptureSamples(CaptureDevice, &Samples[Start], SamplesAvailable);
    }

    // Save the file
    uuid_t id;
    uuid_generate(id);
    char *string = new char[30];
    uuid_unparse(id, string);
    std::string uuid = string;
    std::string str = TMP_DIR + uuid + ".wav";
    std::cout << "Sound file generated at :" << str << std::endl;
    SaveSound(str, Samples);
    emit newSoundCreated(QString::fromStdString(str));
    
    Samples.clear();
    return 0;
}