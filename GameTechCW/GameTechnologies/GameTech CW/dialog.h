#ifndef DIALOG_H
#define DIALOG_H

#include "..\..\Qt\include\QtWidgets\qdialog.h"
#include "mainwindow.h"
#include "..\..\Qt\include\QtWidgets\qmainwindow.h"
#include "..\..\Qt\include\QtGui\QtGui"
#include "..\..\Qt\include\QtCore\qdebug.h"
#include "..\..\Qt\include\QtWidgets\qmessagebox.h"
#include "..\..\Qt\include\QtWidgets\qlabel.h"
#include "..\..\Qt\include\QtWidgets\qslider.h"
#include "..\..\Qt\include\QtWidgets\QVBoxLayout"
#include "..\..\Qt\include\QtGui\qwindow.h"
#include "..\..\Qt\include\QtCore\qstring.h"
#include <string>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
	//window instance
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

 //slots are events, self explanatory names
private slots:
    void on_horizontalSlider_3_valueChanged(int value);

    void on_enterplayername_textEdited(const QString &arg1);

    void on_sizeslider_valueChanged(int value);

    void on_skillslider_valueChanged(int value);

    void on_texslider_valueChanged(int value);

    void on_acceptbutton_clicked();

private:
   Ui::Dialog *ui;
};

#endif // DIALOG_H
