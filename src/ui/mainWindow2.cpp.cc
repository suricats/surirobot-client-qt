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
#include "mainWindow2.h"
#define NB_WIDGETS 3
mainWindow2::mainWindow2() :
ui(new Ui:mainWindow2)
{
    ui->setupUi(this);
    QPixmap pix("img/SuriRobot2.png");
    ui->labelPicture->setPixmap(pix);

    widget.setupUi(this);
    keyPressEventHandler* eKeyPress = new keyPressEventHandler();
    installEventFilter(eKeyPress);

    //Image
    imgWidget = new QWidget(this);
    labelImage = new QLabel(imgWidget);
    labelImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     //Font
    QFont f("Roboto", 40, QFont::Bold);
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

    //Background color
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

mainWindow2::~mainWindow2() {
  delete ui;
}
void mainWindow2::smartShow()
{
    showFullScreen();
    updateWidgets();
    //Timer display fixer
    QTimer* displayFixer = new QTimer(this);
    displayFixer->setInterval(3000);
    //displayFixer->setSingleShot(true);
    QObject::connect(displayFixer, SIGNAL(timeout()), this, SLOT(updateSlot()));
    displayFixer->start();

}
void mainWindow2::setTextUpFont(const QFont& f)
{
    labelTextUp->setFont(f);
    updateWidgets();
}
void mainWindow2::setTextUp(const QString& text)
{
    labelTextUp->setText(text);
    updateWidgets();
}
void mainWindow2::setTextMiddle(const QString& text)
{
    labelTextMiddle->setText(text);
    updateWidgets();
}
void mainWindow2::setTextDown(const QString& text)
{
    labelTextDown->setText(text);
    updateWidgets();
}
void mainWindow2::setImage(QImage& image)
{
    labelImage->setPixmap(QPixmap::fromImage(image));
    imgWidget->resize(image.height(),image.width());
    updateWidgets();

}
void mainWindow2::setEditText()
{
    editText = new QTextEdit();
    editText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    editText->show();
    updateWidgets();
}
QString mainWindow2::getEditText()
{
    return editText->toPlainText();
}
void mainWindow2::sendEditText()
{
    emit sendEditTextSignal(editText->toPlainText());
}

void mainWindow2::updateWidgets()
{
    labelTextUp->adjustSize();
    labelTextMiddle->adjustSize();
    labelTextDown->adjustSize();
    imgWidget->adjustSize();

    imgWidget->move(this->width()/2-imgWidget->width()/2,this->height()/3-imgWidget->height()/2);
    labelTextUp->move(this->width()/2-this->labelTextUp->width()/2,this->height()/3-this->labelTextUp->height()/2+imgWidget->height()/2);
    labelTextMiddle->move(this->width()/2-this->labelTextUp->width()/2,this->height()/3-this->labelTextUp->height()/2+imgWidget->height()/2+this->labelTextUp->height());
    labelTextDown->move(this->width()/2-this->labelTextUp->width()/2,this->height()/3-this->labelTextUp->height()/2+imgWidget->height()/2+this->labelTextUp->height()+this->labelTextMiddle->height());
}
void mainWindow2::updateSlot()
{
    updateWidgets();
}

///SIGNALS
void mainWindow2::setTextUpSignal(QString text) {
    this->setTextUp(text);
    this->updateWidgets();
}

void mainWindow2::setTextMiddleSignal(QString text) {
    this->setTextMiddle(text);
    this->updateWidgets();
}
void mainWindow2::setTextDownSignal(QString text) {
    this->setTextDown(text);
    this->updateWidgets();
}
