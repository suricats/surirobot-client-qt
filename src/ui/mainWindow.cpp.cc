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

    //ui->setupUi(this);
    widget.setupUi(this);
    

    //Image
    imgWidget = new QWidget(this);
    labelImage = new QLabel(imgWidget);
    labelImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QImage image;
    image.load(NORMAL_IMAGE);
    labelImage->setPixmap(QPixmap::fromImage(image));
    imgWidget->resize(image.height(), image.width());
    //Font
    QFont f("Roboto", 16, QFont::Bold);
    //Text Up
    labelTextUp = new QLabel(this);
    labelTextUp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labelTextUp->setFont(f);
    labelTextUp->setText("N/A");

    //Text Middle
    labelTextMiddle = new QLabel(this);
    labelTextMiddle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labelTextMiddle->setFont(f);
    labelTextMiddle->setText("N/A");

    //Text Down
    labelTextDown = new QLabel(this);
    labelTextDown->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labelTextDown->setFont(f);
    labelTextDown->setText("N/A");

    //Microphone button
    MicButton = new QPushButton(this);
    MicButton->setIcon(QIcon(MICRO_IMAGE));
    MicButton->setIconSize(QSize(65, 65));
    QPalette paltt = MicButton->palette();
    paltt.setColor(QPalette::Button, QColor(Qt::white));
    MicButton->setAutoFillBackground(true);
    MicButton->setPalette(paltt);
    MicButton->update();

    //Manuel button
    Manuel = new QPushButton(this);
    Manuel->setText("Manuel");
    connect(Manuel, SIGNAL(clicked()), this, SLOT(createManualWindow()));

    //Background color
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

mainWindow::~mainWindow() {

}

void mainWindow::smartShow() {
    showFullScreen();
    updateWidgets();
    //Timer display fixer
    QTimer* displayFixer = new QTimer(this);
    displayFixer->setInterval(3000);
    //displayFixer->setSingleShot(true);
    QObject::connect(displayFixer, SIGNAL(timeout()), this, SLOT(updateSlot()));
    displayFixer->start();

}

void mainWindow::setTextUpFont(const QFont& f) {
    labelTextUp->setFont(f);
    updateWidgets();
}

void mainWindow::setTextUp(const QString& text) {
    labelTextUp->setText(text);
    updateWidgets();
}

void mainWindow::setTextMiddle(const QString& text) {
    labelTextMiddle->setText(text);
    updateWidgets();
}

void mainWindow::setTextDown(const QString& text) {
    labelTextDown->setText(text);
    updateWidgets();
}

void mainWindow::setImage(QImage& image) {
    labelImage->setPixmap(QPixmap::fromImage(image));
    imgWidget->resize(image.height(), image.width());
    updateWidgets();

}

void mainWindow::setEditText() {
    editText = new QTextEdit();
    editText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    editText->show();
    updateWidgets();
}

QString mainWindow::getEditText() {
    return editText->toPlainText();
}

void mainWindow::sendEditText() {
    emit sendEditTextSignal(editText->toPlainText());
}

void mainWindow::updateWidgets() {
    labelTextUp->adjustSize();
    labelTextMiddle->adjustSize();
    labelTextDown->adjustSize();
    imgWidget->adjustSize();

    imgWidget->move(this->width() / 2 - imgWidget->width() / 2, this->height() / 3 - imgWidget->height() / 2);
    labelTextUp->move(this->width() / 2 - this->labelTextUp->width() / 2, this->height() / 3 - this->labelTextUp->height() / 2 + imgWidget->height() / 2);
    labelTextMiddle->move(this->width() / 2 - this->labelTextUp->width() / 2, this->height() / 3 - this->labelTextUp->height() / 2 + imgWidget->height() / 2 + this->labelTextUp->height());
    labelTextDown->move(this->width() / 2 - this->labelTextUp->width() / 2, this->height() / 3 - this->labelTextUp->height() / 2 + imgWidget->height() / 2 + this->labelTextUp->height() + this->labelTextMiddle->height());
}

void mainWindow::updateSlot() {
    updateWidgets();
}

///SIGNALS

void mainWindow::setTextUpSignal(QString text) {
    this->setTextUp(text);
    this->updateWidgets();
}

void mainWindow::setTextMiddleSignal(QString text) {
    this->setTextMiddle(text);
    this->updateWidgets();
}

void mainWindow::setTextDownSignal(QString text) {
    this->setTextDown(text);
    this->updateWidgets();
}

//Slots

void mainWindow::createManualWindow() //create new manual window
{
    manualWindow* manualW = new manualWindow();
    manualW->show();
}
