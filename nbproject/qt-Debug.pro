# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = surirobot-client-qt
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network
SOURCES += src/api/APICaller.cpp src/api/ConverseAPICaller.cpp src/api/EmotionalAPICaller.cpp src/api/EmotionalAPICaller_old.cpp src/keyPressEventHandler.cpp src/main.cpp src/redis/QTRedis.cpp src/ui/mainWindow.cpp.cc
HEADERS += src/api/APICaller.hpp src/api/ConverseAPICaller.hpp src/api/EmotionalAPICaller.hpp src/api/EmotionalAPICaller_old.hpp src/keyPressEventHandler.h src/qt.h src/ui/mainWindow.h
FORMS += src/ui/mainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
