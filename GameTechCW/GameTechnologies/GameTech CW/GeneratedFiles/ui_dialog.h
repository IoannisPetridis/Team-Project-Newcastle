/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

//#include <QtCore/QVariant>
#include "..\..\..\Qt\include\QtCore\qvariant.h"
//#include <QtWidgets/QAction>
#include "..\..\..\Qt\include\QtWidgets\qaction.h"
//#include <QtWidgets/QApplication>
#include "..\..\..\Qt\include\QtWidgets\qapplication.h"
//#include <QtWidgets/QButtonGroup>
#include "..\..\..\Qt\include\QtWidgets\qbuttongroup.h"
//#include <QtWidgets/QDialog>
#include "..\..\..\Qt\include\QtWidgets\qdialog.h"
//#include <QtWidgets/QHBoxLayout>
#include "..\..\..\Qt\include\QtWidgets\qhboxlayout"
//#include <QtWidgets/QHeaderView>
#include "..\..\..\Qt\include\QtWidgets\qheaderview.h"
//#include <QtWidgets/QLabel>
#include "..\..\..\Qt\include\QtWidgets\qlabel.h"
//#include <QtWidgets/QLineEdit>
#include "..\..\..\Qt\include\QtWidgets\qlineedit.h"
//#include <QtWidgets/QPushButton>
#include "..\..\..\Qt\include\QtWidgets\qpushbutton.h"
//#include <QtWidgets/QSlider>
#include "..\..\..\Qt\include\QtWidgets\qslider.h"
//#include <QtWidgets/QVBoxLayout>
#include "..\..\..\Qt\include\QtWidgets\QVboxlayout"
//#include <QtWidgets/QWidget>
#include "..\..\..\Qt\include\QtWidgets\qwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *acceptbutton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *sizelabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *skilllabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *texlabel;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QLabel *namelabel;
    QLineEdit *enterplayername;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QSlider *sizeslider;
    QSlider *skillslider;
    QSlider *texslider;
    QLabel *textcubeimg;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(584, 377);
        QFont font;
        font.setFamily(QStringLiteral("CordiaUPC"));
        font.setPointSize(16);
        Dialog->setFont(font);
        acceptbutton = new QPushButton(Dialog);
        acceptbutton->setObjectName(QStringLiteral("acceptbutton"));
        acceptbutton->setGeometry(QRect(220, 320, 151, 31));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 70, 231, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        sizelabel = new QLabel(layoutWidget);
        sizelabel->setObjectName(QStringLiteral("sizelabel"));

        horizontalLayout_2->addWidget(sizelabel);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 140, 231, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        skilllabel = new QLabel(layoutWidget1);
        skilllabel->setObjectName(QStringLiteral("skilllabel"));

        horizontalLayout_3->addWidget(skilllabel);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 200, 231, 31));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        texlabel = new QLabel(layoutWidget2);
        texlabel->setObjectName(QStringLiteral("texlabel"));

        horizontalLayout_4->addWidget(texlabel);

        layoutWidget3 = new QWidget(Dialog);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 0, 551, 42));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        namelabel = new QLabel(layoutWidget3);
        namelabel->setObjectName(QStringLiteral("namelabel"));
        QFont font1;
        font1.setPointSize(18);
        namelabel->setFont(font1);

        horizontalLayout->addWidget(namelabel, 0, Qt::AlignHCenter);

        enterplayername = new QLineEdit(layoutWidget3);
        enterplayername->setObjectName(QStringLiteral("enterplayername"));
        enterplayername->setFont(font1);

        horizontalLayout->addWidget(enterplayername);

        layoutWidget4 = new QWidget(Dialog);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(20, 70, 321, 241));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        sizeslider = new QSlider(layoutWidget4);
        sizeslider->setObjectName(QStringLiteral("sizeslider"));
        sizeslider->setMinimum(1);
        sizeslider->setMaximum(4);
        sizeslider->setOrientation(Qt::Horizontal);
        sizeslider->setTickPosition(QSlider::TicksAbove);
        sizeslider->setTickInterval(1);

        verticalLayout->addWidget(sizeslider);

        skillslider = new QSlider(layoutWidget4);
        skillslider->setObjectName(QStringLiteral("skillslider"));
        skillslider->setMinimum(1);
        skillslider->setMaximum(3);
        skillslider->setOrientation(Qt::Horizontal);
        skillslider->setTickPosition(QSlider::TicksAbove);
        skillslider->setTickInterval(1);

        verticalLayout->addWidget(skillslider);

        texslider = new QSlider(layoutWidget4);
        texslider->setObjectName(QStringLiteral("texslider"));
        texslider->setMinimum(1);
        texslider->setMaximum(3);
        texslider->setOrientation(Qt::Horizontal);
        texslider->setTickPosition(QSlider::TicksAbove);
        texslider->setTickInterval(1);

        verticalLayout->addWidget(texslider);

        textcubeimg = new QLabel(Dialog);
        textcubeimg->setObjectName(QStringLiteral("textcubeimg"));
        textcubeimg->setGeometry(QRect(380, 160, 271, 211));
        textcubeimg->setPixmap(QPixmap(QString::fromUtf8("checkertexture150x125.png")));
#ifndef QT_NO_SHORTCUT
        namelabel->setBuddy(enterplayername);
#endif // QT_NO_SHORTCUT

        retranslateUi(Dialog);
        QObject::connect(sizeslider, SIGNAL(valueChanged(int)), sizelabel, SLOT(setNum(int)));
        QObject::connect(skillslider, SIGNAL(valueChanged(int)), skilllabel, SLOT(setNum(int)));
        QObject::connect(acceptbutton, SIGNAL(clicked(bool)), Dialog, SLOT(close()));
        QObject::connect(texslider, SIGNAL(valueChanged(int)), texlabel, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        acceptbutton->setText(QApplication::translate("Dialog", "Accept", 0));
        label->setText(QApplication::translate("Dialog", "Cube Size:", 0));
        sizelabel->setText(QApplication::translate("Dialog", "Small", 0));
        label_2->setText(QApplication::translate("Dialog", "Special Ability:", 0));
        skilllabel->setText(QApplication::translate("Dialog", "Shrink & Boost", 0));
        label_3->setText(QApplication::translate("Dialog", "Texture:", 0));
        texlabel->setText(QApplication::translate("Dialog", "Checker", 0));
        namelabel->setText(QApplication::translate("Dialog", "Name:", 0));
        enterplayername->setText(QApplication::translate("Dialog", "Enter player  name...", 0));
        textcubeimg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
