/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Thomas
 *
 * Created on 10 octobre 2017, 22:28
 */

#include <QApplication>
#include <QImage>
#include <QtWidgets/QLabel>
#include <QGridLayout>
#include <QRect>
#include <QDesktopWidget>
/*
#include <QPushButton>
#include <QWidget>

 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <QtWidgets/qlayout.h>
#include "keyPressEventHandler.h"
#include "mainWindow.h"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;


    QApplication app(argc, argv);
    mainWindow* window = new mainWindow();
    
    //Image
    QImage imageNormal;
    imageNormal.load("./img/Surirobot1.png");
    window->setImage(imageNormal);
    
    //Text
    QFont f( "Arial", 40, QFont::Bold);
    window->setTextFont(f);
    window->setText("Salut !");
    window->showFullScreen();
    
    window->smartShow();
    return app.exec();


}
