/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   keyPressEventHandler.cpp
 * Author: Alain BERRIER
 * 
 * Created on 2 décembre 2017, 16:42
 */

#include "keyPressEventHandler.h"

keyPressEventHandler::keyPressEventHandler() {
}


keyPressEventHandler::~keyPressEventHandler() {
}

bool keyPressEventHandler::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Escape) || (key->key()==Qt::Key_Return) ) {
            QApplication::quit();
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}