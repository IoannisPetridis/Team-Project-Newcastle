#include "dialog.h"
#include "GeneratedFiles/ui_dialog.h"
#include "..\..\Qt\include\QtCore\qstring.h"
#include <iostream> //for std

//set initial to 1 in case window is opened but sliders not moved
int Dialog::sizechoice = 1;
int Dialog::skillchoice = 1;
int Dialog::texchoice = 1;
std::string Dialog::playerusername = "Player1";

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

//saves player name when the input box is edited
void Dialog::on_enterplayername_textEdited(const QString &arg1)
{
	//save player input as qstring
	playername = arg1;

	//convert qstring playername to string
	Dialog::qstringtostring(playername);
}

//saves sizechoice when sizeslider moved
void Dialog::on_sizeslider_valueChanged(int value)
{
	if (value == 1) {
		this->ui->sizelabel->setText("Small");
	}
	if (value == 2) {
		this->ui->sizelabel->setText("Medium");
	}
	if (value == 3) {
		this->ui->sizelabel->setText("Large");
	}
	if (value == 4) {
		this->ui->sizelabel->setText("XLarge");
	}

	sizechoice = value;
}

//saves skillchoice when skillslider moved
void Dialog::on_skillslider_valueChanged(int value)
{
	if (value == 1) {
		this->ui->skilllabel->setText("Shrink & Boost");
	}
	if (value == 2) {
		this->ui->skilllabel->setText("Gravity Gun");
	}
	if (value == 3) {
		this->ui->skilllabel->setText("Tron");
	}

	Dialog::skillchoice = value;
}

//saves texchoice when texslider moved
void Dialog::on_texslider_valueChanged(int value)
{
	if (value == 1) {
		this->ui->texlabel->setText("Checker");
	}
	if (value == 2) {
		this->ui->texlabel->setText("Something1");
	}
	if (value == 3) {
		this->ui->texlabel->setText("Something2");
	}

	if (value == 1) {
		this->ui->textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertexture150x125.png"));
		//qDebug() << "File exists -" << QFileInfo("checkertexture150x125.png").exists() << " " << QFileInfo("checkertexture150x125.png").absoluteFilePath(); //test if file exists
	}
	if (value == 2) {
		this->ui->textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertexturepink150x125.png"));
	}
	if (value == 3) {
		this->ui->textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertextureblue150x125.png"));
	}

	texchoice = value;
}

//when accept is clicked, the user values from dialog are transferred to mainwindow class using a temp mainwindow
void Dialog::on_acceptbutton_clicked()
{
	MainWindow sendinguserdata;

	sendinguserdata.grabuserdata(sizechoice, skillchoice, texchoice, playerusername);
}

void Dialog::on_horizontalSlider_3_valueChanged(int) {} //this shit doesnt exist anymore but deleting it throws an error so...

