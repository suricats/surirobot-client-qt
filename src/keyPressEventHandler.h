/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   keyPressEventHandler.h
 * Author: Alain BERRIER
 *
 * Created on 2 décembre 2017, 16:42
 */

#ifndef KEYPRESSEVENTHANDLER_H
#define KEYPRESSEVENTHANDLER_H

#include <QtCore/qobject.h>
#include <QKeyEvent>
#include <QKeySequence>
#include <QApplication>
#include <QTime>
#include "controller/converseManager.hpp"

class keyPressEventHandler : public QObject {
    Q_OBJECT
public:
    keyPressEventHandler();
    virtual ~keyPressEventHandler();
    bool onScenario;
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:
    converseManager* cm;
    SpeechRecording* sr;
    bool audioRecording;
    QTimer* expirationTimer;
signals:
    void startRecord();
    void stopRecord();
private slots:
    void manageRecord(bool val);


};

#endif /* KEYPRESSEVENTHANDLER_H */

