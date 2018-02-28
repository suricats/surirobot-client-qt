/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manualWindow.cpp
 * Author: Thomas Dufour
 * 
 * Created on February 28, 2018, 11:01 AM
 */

#include "manualWindow.h"


#define NB_WIDGETS 3
manualWindow::manualWindow()
{
	Mwidget.setupUi(this);
	//Font
         QFont f("Roboto", 40, QFont::Bold);
	setFixedSize(500, 500);
	setWindowTitle("Mode Manuel");
	this->show();
}

manualWindow::~manualWindow() {}