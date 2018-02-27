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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QFrame *frame;
    QPushButton *ButtonM;
    QPushButton *ButtonMic;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelPicture;

    void setupUi(QDialog *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QStringLiteral("mainWindow"));
        mainWindow->resize(990, 680);
        frame = new QFrame(mainWindow);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-10, 0, 1061, 681));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        ButtonM = new QPushButton(frame);
        ButtonM->setObjectName(QStringLiteral("ButtonM"));
        ButtonM->setGeometry(QRect(860, 110, 99, 27));
        ButtonMic = new QPushButton(frame);
        ButtonMic->setObjectName(QStringLiteral("ButtonMic"));
        ButtonMic->setGeometry(QRect(860, 430, 91, 71));
        QIcon icon;
        icon.addFile(QStringLiteral("../../img/mic.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonMic->setIcon(icon);
        ButtonMic->setIconSize(QSize(30, 30));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(350, 420, 251, 181));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 261, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelPicture = new QLabel(frame);
        labelPicture->setObjectName(QStringLiteral("labelPicture"));
        labelPicture->setGeometry(QRect(290, 120, 381, 241));

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QDialog *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "mainWindow", 0));
        ButtonM->setText(QApplication::translate("mainWindow", "Manuel", 0));
        ButtonMic->setText(QString());
        groupBox->setTitle(QApplication::translate("mainWindow", "GroupBox", 0));
        labelPicture->setText(QApplication::translate("mainWindow", "<html><head/><body><p><br/></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
