# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/linux-debug/GNU-Linux
TARGET = surirobot-client-qt
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network
SOURCES += src/controller/converseManager.cpp src/controller/faceManager.cpp src/controller/generalManager.cpp src/keyPressEventHandler.cpp src/main.cpp src/model/api/APICaller.cpp src/model/api/ConverseAPICaller.cpp src/model/api/EmotionalAPICaller.cpp src/model/api/FileDownloader.cpp src/model/api/NLPAPICaller.cpp src/model/api/STTAPiCaller.cpp src/model/redis/QTRedis.cpp src/model/sound/MusicPlayer.cpp src/model/sound/SpeechRecording.cpp src/ui/mainWindow.cpp.cc src/ui/manualWindow.cpp
HEADERS += src/conf.hpp src/controller/converseManager.hpp src/controller/faceManager.hpp src/controller/generalManager.hpp src/keyPressEventHandler.h src/model/api/APICaller.hpp src/model/api/ConverseAPICaller.hpp src/model/api/EmotionalAPICaller.hpp src/model/api/FileDownloader.hpp src/model/api/NLPAPICaller.hpp src/model/api/STTAPiCaller.hpp src/model/redis/QTRedis.hpp src/model/sound/MusicPlayer.hpp src/model/sound/SpeechRecording.hpp src/qt.h src/ui/mainWindow.h src/ui/manualWindow.h
FORMS += src/ui/mainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/linux-debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libhiredis.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopencv_core.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopencv_highgui.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopenal.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libsndfile.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libuuid.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libavutil.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libavdevice.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libalut.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libSDL2.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
