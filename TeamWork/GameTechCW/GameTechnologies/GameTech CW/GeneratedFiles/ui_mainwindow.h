/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

//#include <QtCore/QVariant>
#include "..\..\..\Qt\include\QtCore\qvariant.h"
//#include <QtWidgets/QAction>
#include "..\..\..\Qt\include\QtWidgets\qaction.h"
//#include <QtWidgets/QApplication>
#include "..\..\..\Qt\include\QtWidgets\qapplication.h"
//#include <QtWidgets/QButtonGroup>
#include "..\..\..\Qt\include\QtWidgets\qbuttongroup.h"
//#include <QtWidgets/QHeaderView>
#include "..\..\..\Qt\include\QtWidgets\qheaderview.h"
//#include <QtWidgets/QLabel>
#include "..\..\..\Qt\include\QtWidgets\qlabel.h"
//#include <QtWidgets/QMainWindow>
#include "..\..\..\Qt\include\QtWidgets\qmainwindow.h"
//#include <QtWidgets/QMenuBar>
#include "..\..\..\Qt\include\QtWidgets\qmenubar.h"
//#include <QtWidgets/QPushButton>
#include "..\..\..\Qt\include\QtWidgets\qpushbutton.h"
//#include <QtWidgets/QStatusBar>
#include "..\..\..\Qt\include\QtWidgets\qstatusbar.h"
//#include <QtWidgets/QToolBar>
#include "..\..\..\Qt\include\QtWidgets\qtoolbar.h"
//#include <QtWidgets/QVBoxLayout>
#include "..\..\..\Qt\include\QtWidgets\QVboxlayout"
//#include <QtWidgets/QWidget>
#include "..\..\..\Qt\include\QtWidgets\qwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCreate_Character;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QPushButton *exitbutton;
    QPushButton *createcharabutton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 400);
        QFont font;
        font.setFamily(QStringLiteral("CordiaUPC"));
        font.setPointSize(16);
        MainWindow->setFont(font);
        QIcon icon;
        QString iconThemeName = QStringLiteral("fg");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionCreate_Character = new QAction(MainWindow);
        actionCreate_Character->setObjectName(QStringLiteral("actionCreate_Character"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 50, 247, 136));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("CordiaUPC"));
        font1.setPointSize(28);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        exitbutton = new QPushButton(layoutWidget);
        exitbutton->setObjectName(QStringLiteral("exitbutton"));
        exitbutton->setMinimumSize(QSize(243, 0));

        verticalLayout->addWidget(exitbutton);

        createcharabutton = new QPushButton(layoutWidget);
        createcharabutton->setObjectName(QStringLiteral("createcharabutton"));
        createcharabutton->setIconSize(QSize(16, 16));
        createcharabutton->setAutoDefault(false);
        createcharabutton->setFlat(false);

        verticalLayout->addWidget(createcharabutton);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(exitbutton, SIGNAL(clicked(bool)), MainWindow, SLOT(close()));

        createcharabutton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCreate_Character->setText(QApplication::translate("MainWindow", "Create Character", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Character->setToolTip(QApplication::translate("MainWindow", "Create Character", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "ROCKET LEAGUE V2", 0));
        exitbutton->setText(QApplication::translate("MainWindow", "Play", 0));
        createcharabutton->setText(QApplication::translate("MainWindow", "Create Character", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
