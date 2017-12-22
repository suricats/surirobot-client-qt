# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/MinGW_64-Windows
TARGET = surirobot-client-qt
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network
SOURCES += connectors/redis/QTRedis.cpp keyPressEventHandler.cpp main.cpp mainWindow.cpp.cc
HEADERS += connectors/redis/QTRedis.hpp keyPressEventHandler.h lib/hiredis/include/adapters/qt.h mainWindow.h
FORMS += mainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/MinGW_64-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
