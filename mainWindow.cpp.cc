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
#define NB_WIDGETS 3
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
    
    //Background color
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

mainWindow::~mainWindow() {
}
void mainWindow::smartShow()
{
    showFullScreen();
    updateWidgets();
    //Timer display fixer
    QTimer* displayFixer = new QTimer(this);
    displayFixer->setInterval(100);
    displayFixer->setSingleShot(true);
    QObject::connect(displayFixer, SIGNAL(timeout()), this, SLOT(updateSlot()));
    displayFixer->start();
}
void mainWindow::setTextFont(const QFont& f)
{
    labelText->setFont(f);
    updateWidgets();
}
void mainWindow::setText(const QString& text)
{
    labelText->setText(text);
    updateWidgets();
}
void mainWindow::setImage(QImage& image)
{
    labelImage->setPixmap(QPixmap::fromImage(image));
    imgWidget->resize(image.height(),image.width());
    updateWidgets();
    
}
void mainWindow::setEditText()
{
    editText = new QTextEdit();
    editText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    editText->show();
    updateWidgets();
}
QString mainWindow::getEditText()
{
    return editText->toPlainText();
}
void mainWindow::sendEditText()
{
    emit sendEditText_signal(editText->toPlainText());
}

void mainWindow::updateWidgets()
{
    labelText->adjustSize();
    imgWidget->adjustSize();
    imgWidget->move(this->width()/2-imgWidget->width()/2,this->height()/2-imgWidget->height()/2);
    labelText->move(this->width()/2-this->labelText->width()/2,this->height()/2-this->labelText->height()/2+imgWidget->height()/2);
}
void mainWindow::updateSlot()
{
    updateWidgets();
}
void mainWindow::changeText(QString text) {
    this->setText(text);
    this->updateWidgets();
}
