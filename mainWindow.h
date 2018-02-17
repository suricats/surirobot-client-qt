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
#include "keyPressEventHandler.h"
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QTextEdit>

class mainWindow : public QDialog {
    Q_OBJECT
public:
    mainWindow();
    virtual ~mainWindow();
    void smartShow();
    void setTextFont(const QFont&);
    void setText(const QString&);
    void setEditText();
    QString getEditText();
    void setImage(QImage&);
    void updateWidgets();
    

public slots:
    void changeText(QString text);
    void sendEditText();
signals:
    void sendEditText_signal(QString text);
private:
    QWidget* imgWidget;
    QLabel* labelImage;
    QTextEdit* editText;
    QImage currentImage;
    QLabel* labelText;
    Ui::mainWindow widget;
};

#endif /* _MAINWINDOW_H */
