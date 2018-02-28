# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux
TARGET = surirobot-client-qt
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += src/controller/converseManager.cpp src/keyPressEventHandler.cpp src/main.cpp src/model/SpeechRecording.cpp src/model/api/APICaller.cpp src/model/api/ConverseAPICaller.cpp src/model/api/EmotionalAPICaller.cpp src/model/api/EmotionalAPICaller_old.cpp src/model/api/NLPAPICaller.cpp src/model/redis/QTRedis.cpp src/ui/mainWindow.cpp.cc src/ui/manualWindow.cpp
HEADERS += src/conf.hpp src/controller/converseManager.hpp src/keyPressEventHandler.h src/model/SpeechRecording.hpp src/model/api/APICaller.hpp src/model/api/ConverseAPICaller.hpp src/model/api/EmotionalAPICaller.hpp src/model/api/EmotionalAPICaller_old.hpp src/model/api/NLPAPICaller.hpp src/model/redis/QTRedis.hpp src/qt.h src/ui/mainWindow.h src/ui/manualWindow.h
FORMS += src/ui/mainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
