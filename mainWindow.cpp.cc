/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   mainWindow.cpp
 * Author: Alain BERRIER
 *
 * Created on 21 décembre 2017, 16:22
 */

#include "mainWindow.h"

mainWindow::mainWindow() {
    widget.setupUi(this);
    keyPressEventHandler* eKeyPress = new keyPressEventHandler();
    installEventFilter(eKeyPress);
    
    //Image
    imgWidget = new QWidget(this);
    labelImage = new QLabel(imgWidget);
    labelImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    
    //Text
    labelText = new QLabel(this);
    labelText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labelText->setText("N/A");
}

mainWindow::~mainWindow() {
}
void mainWindow::smartShow()
{
    showFullScreen();
    updateWidgets();
}
void mainWindow::setTextFont(const QFont& f)
{
    labelText->setFont(f);
}
void mainWindow::setText(const QString& text)
{
    labelText->setText(text);
}
void mainWindow::setImage(QImage& image)
{
    labelImage->setPixmap(QPixmap::fromImage(image));
    imgWidget->resize(image.height(),image.width());
    
}
void mainWindow::updateWidgets()
{
    this->imgWidget->move(this->width()/2-imgWidget->width()/2,this->height()/2-imgWidget->height()/2);
    this->labelText->move(this->width()/2-this->labelText->width()/2,this->height()/2-this->labelText->height()/2+imgWidget->height()/2);
}

void mainWindow::changeText(const QString& text) {
    this->setText(text);
    this->updateWidgets();
}
