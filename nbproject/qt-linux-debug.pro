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
SOURCES += src/SpeechRecording.cpp src/api/APICaller.cpp src/api/ConverseAPICaller.cpp src/api/EmotionalAPICaller.cpp src/api/NLPAPICaller.cpp src/keyPressEventHandler.cpp src/main.cpp src/redis/QTRedis.cpp src/ui/mainWindow.cpp.cc src/ui/manualWindow.cpp
HEADERS += src/SpeechRecording.hpp src/api/APICaller.hpp src/api/ConverseAPICaller.hpp src/api/EmotionalAPICaller.hpp src/api/NLPAPICaller.hpp src/conf.hpp src/keyPressEventHandler.h src/qt.h src/redis/QTRedis.hpp src/ui/mainWindow.h src/ui/manualWindow.h
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
LIBS += -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libhiredis.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopencv_core.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopencv_highgui.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libopenal.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libsndfile.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libuuid.so  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
