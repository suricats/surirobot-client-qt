/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   mainWindow.h
 * Author: Alain BERRIER
 *
 * Created on 21 décembre 2017, 16:22
 */

#ifndef _MAINWINDOW2_H
#define _MAINWINDOW2_H

#include "ui_mainWindow2.h"
#include "../keyPressEventHandler.h"
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>
#include <QPixmap>
#include <QPushButton>

class mainWindow2 : public QDialog {
    Q_OBJECT
public:
    mainWindow2();
    virtual ~mainWindow2();
    void smartShow();
    void setTextUpFont(const QFont&);
    void setTextUp(const QString&);
    void setTextMiddle(const QString&);
    void setTextDown(const QString&);
    void setEditText();
    QString getEditText();
    void setImage(QImage&);
    void updateWidgets();


public slots:
    void setTextUpSignal(QString text);
    void setTextMiddleSignal(QString text);
    void setTextDownSignal(QString text);
    void sendEditText();
    void updateSlot();
signals:
    void sendEditTextSignal(QString text);
private:


    QWidget* imgWidget;
    QLabel* labelImage;
    QTextEdit* editText;
    QImage currentImage;
    QLabel* labelTextUp;
    QLabel* labelTextMiddle;
    QLabel* labelTextDown;
    Ui::mainWindow2 widget;
};

#endif /* _MAINWINDOW_H */
