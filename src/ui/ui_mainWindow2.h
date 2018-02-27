/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QPixmap>
QT_BEGIN_NAMESPACE

class Ui_mainWindow2
{
public:

    void setupUi(QDialog *mainWindow2)
    {
        if (mainWindow2->objectName().isEmpty())
            mainWindow2->setObjectName(QStringLiteral("mainWindow2"));
        mainWindow2->resize(400, 300);

        retranslateUi(mainWindow2);

        QMetaObject::connectSlotsByName(mainWindow2);
    } // setupUi

    void retranslateUi(QDialog *mainWindow2)
    {
        mainWindow2->setWindowTitle(QApplication::translate("mainWindow2", "mainWindow2", 0));
    } // retranslateUi

};

namespace Ui {
    class mainWindow2: public Ui_mainWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
