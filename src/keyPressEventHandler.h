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
#include <QApplication>

class keyPressEventHandler : public QObject {
    Q_OBJECT
public:
    keyPressEventHandler();
    virtual ~keyPressEventHandler();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:


};

#endif /* KEYPRESSEVENTHANDLER_H */

