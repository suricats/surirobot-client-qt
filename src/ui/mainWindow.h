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

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "ui_mainWindow.h"
#include "manualWindow.h"
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>
#include <QPushButton>

#define NORMAL_IMAGE "res/SuriRobot1.png"
#define MICRO_IMAGE "res/mic.png"
class mainWindow : public QDialog {
    Q_OBJECT
public:
    
    QPushButton *MicButton;
    QPushButton* Manuel;
    
    mainWindow();
    virtual ~mainWindow();
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
    void createManualWindow(); 
    void setTextUpSignal(QString text);
    void setTextMiddleSignal(QString text);
    void setTextDownSignal(QString text);
    void sendEditText();
    void updateSlot();
signals:
    void sendEditTextSignal(QString text);
    void sendMicSignal();
private:
    QWidget* imgWidget;
    QLabel* labelImage;
    QTextEdit* editText;
    QImage currentImage;
	
    QLabel* labelTextUp;
    QLabel* labelTextMiddle;
    QLabel* labelTextDown;
	
    Ui::mainWindow widget;
};

#endif /* _MAINWINDOW_H */
