#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"

#include "..\..\Qt\include\QtWidgets\qdialog.h"
#include "..\..\Qt\include\QtWidgets\qgridlayout.h"
#include "..\..\Qt\include\QtWidgets\qhboxlayout"
#include "..\..\Qt\include\QtWidgets\qlabel.h"
#include "..\..\Qt\include\QtWidgets\qpushbutton.h"
#include "..\..\Qt\include\QtWidgets\qslider.h"
#include "..\..\Qt\include\QtWidgets\qlineedit.h"
#include "..\..\Qt\include\QtCore\qobject.h"
#include "..\..\Qt\include\QtGui\qpixmap.h"
#include "..\..\Qt\include\QtGui\qfont.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    //window layouts
    QGridLayout *gridlayout;
    QHBoxLayout *usernamelayout;
    QHBoxLayout *sizelayout;
    QHBoxLayout *skilllayout;
    QHBoxLayout *texlayout;

    //assets
    QLineEdit *namebox = new QLineEdit("Player1");

    QLabel *namelabel = new QLabel("Name:  ");
    QLabel *sizelabel = new QLabel("Cube Size:  ");
    QLabel *skilllabel = new QLabel("Special Ability (1 use):  ");
    QLabel *texlabel = new QLabel("Texture:  ");
    QLabel *sizeoptions = new QLabel("Small");
    QLabel *skilloptions = new QLabel("Ball Pull");
    QLabel *texoptions = new QLabel("Checker");
    QLabel *textcubeimg = new QLabel;

    QPushButton *acceptbutton = new QPushButton("Accept");

    QSlider *sizeslider = new QSlider;
    QSlider *skillslider = new QSlider;
    QSlider *texslider = new QSlider;

    QFont dialogfont = QFont("CordiaUPC", 16);

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    //player stat variables
    QString playername;
    static std::string playerusername; //(converted)
    static int sizechoice;
    static int skillchoice;
    static int texchoice;

    //converts qstring to string
    void qstringtostring(QString name){
        playerusername = name.toLocal8Bit().constData();
    }

public slots:
    void sizesliderValueChanged(int value);
    void skillsliderValueChanged(int value);
    void texsliderValueChanged(int value);

    void enterplayernameTextEdited(const QString &arg1);
    void acceptbuttonClicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
