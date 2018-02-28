/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manualWindow.h
 * Author: Thomas Dufour
 *
 * Created on February 28, 2018, 11:01 AM
 */

#ifndef MANUALWINDOW_H
#define MANUALWINDOW_H


#include "ui_mainWindow.h"
#include "../keyPressEventHandler.h"
#include "manualWindow.h"
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>
#include <QPushButton>

class manualWindow : public QDialog {
    Q_OBJECT
public:

	manualWindow();
	virtual ~manualWindow();
	
private:
    Ui::mainWindow Mwidget;
};

#endif /* MANUALWINDOW_H */
