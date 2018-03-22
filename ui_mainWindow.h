/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QFrame *frame;
    QLabel *labelImage;

    void setupUi(QDialog *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QStringLiteral("mainWindow"));
        mainWindow->resize(990, 680);
        frame = new QFrame(mainWindow);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-40, 0, 1061, 691));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        labelImage = new QLabel(frame);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(270, 110, 401, 251));

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QDialog *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "mainWindow", 0));
        labelImage->setText(QApplication::translate("mainWindow", "<html><head/><body><p><br/></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
