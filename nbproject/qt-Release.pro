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
SOURCES += src/SpeechRecording.cpp src/api/APICaller.cpp src/api/ConverseAPICaller.cpp src/api/EmotionalAPICaller.cpp src/api/EmotionalAPICaller_old.cpp src/api/NLPAPICaller.cpp src/keyPressEventHandler.cpp src/main.cpp src/redis/QTRedis.cpp src/ui/mainWindow.cpp.cc
HEADERS += src/SpeechRecording.hpp src/api/APICaller.hpp src/api/ConverseAPICaller.hpp src/api/EmotionalAPICaller.hpp src/api/EmotionalAPICaller_old.hpp src/api/NLPAPICaller.hpp src/conf.hpp src/keyPressEventHandler.h src/qt.h src/redis/QTRedis.hpp src/ui/mainWindow.h
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
