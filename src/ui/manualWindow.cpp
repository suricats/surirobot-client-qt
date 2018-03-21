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
	setFixedSize(800, 800);
	setWindowTitle("Mode Manuel");
	
	labelTest = new QLabel(this);
	
	 //ajouter une photo button
    ajoutButton = new QPushButton(this);
   ajoutButton->setText("Ajouter Photo");
	ajoutButton->move(this->width() / 10, this->height() / 10);
	 connect(ajoutButton, SIGNAL(clicked()), this, SLOT(ajout()));
	this->show();
}

manualWindow::~manualWindow() {}

QString manualWindow::browse()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg) "));
   return fileName;
}

void manualWindow::ajout() {
	
	QString fileName;
	fileName = this->browse();
	
	//check si le fichier est lisible
	if (fileName.isEmpty())
			return;
	 else {

		QFile file(fileName);

		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::information(this, tr("Unable to open file"),file.errorString());
		 return;
		}
	 }	
	//check OK	
	
}