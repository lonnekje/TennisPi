/********************************************************************************
** Form generated from reading UI file 'tpc.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TPC_H
#define UI_TPC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TPC
{
public:
    QWidget *centralWidget;
    QLabel *Textlabel;
    QLabel *imglabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TPC)
    {
        if (TPC->objectName().isEmpty())
            TPC->setObjectName(QStringLiteral("TPC"));
        TPC->resize(800, 480);
        TPC->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-style: outset;\n"
"	background-color: \"red\";\n"
"	font: bold 14px;\n"
"	color: rgb(225, 225, 225);\n"
"	font: 11pt \"DejaVu Sans Mono\";\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(96, 208, 114);\n"
"	border-style: inset;\n"
"}\n"
"QWidget{ \n"
"	background-color: rgb(65, 65, 65);\n"
"}"));
        centralWidget = new QWidget(TPC);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Textlabel = new QLabel(centralWidget);
        Textlabel->setObjectName(QStringLiteral("Textlabel"));
        Textlabel->setGeometry(QRect(30, 310, 121, 101));
        Textlabel->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        imglabel = new QLabel(centralWidget);
        imglabel->setObjectName(QStringLiteral("imglabel"));
        imglabel->setGeometry(QRect(200, 10, 591, 401));
        imglabel->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        TPC->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TPC);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 20));
        TPC->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TPC);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TPC->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TPC);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TPC->setStatusBar(statusBar);

        retranslateUi(TPC);

        QMetaObject::connectSlotsByName(TPC);
    } // setupUi

    void retranslateUi(QMainWindow *TPC)
    {
        TPC->setWindowTitle(QApplication::translate("TPC", "TPC", 0));
        Textlabel->setText(QString());
        imglabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TPC: public Ui_TPC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TPC_H
