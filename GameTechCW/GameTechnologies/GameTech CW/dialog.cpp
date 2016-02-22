#include "GeneratedFiles\ui_dialog.h"
#include <iostream>

#include "dialog.h"

//set initial stats to 1 in case window is opened but sliders not moved
int Dialog::sizechoice = 1;
int Dialog::skillchoice = 1;
int Dialog::texchoice = 1;
std::string Dialog::playerusername = "Player1";
QString playername = "Player1";

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {

    //layouts
    ui->setupUi(this);

    gridlayout = new QGridLayout(this);
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->setHorizontalSpacing(15);
    gridlayout->setVerticalSpacing(15);

    usernamelayout = new QHBoxLayout;
    sizelayout = new QHBoxLayout;
    skilllayout = new QHBoxLayout;
    texlayout = new QHBoxLayout;

    //labels
    namelabel->setMinimumHeight(40);
	namelabel->setStyleSheet("border: 0px solid white");
    namebox->setMinimumHeight(40);
	namebox->setStyleSheet("border: 1px solid grey");

	sizelabel->setStyleSheet("border: 0px solid white");
	skilllabel->setStyleSheet("border: 0px solid white");
	texlabel->setStyleSheet("border: 0px solid white");

	sizeoptions->setStyleSheet("border: 0px solid white");
	skilloptions->setStyleSheet("border: 0px solid white");
	texoptions->setStyleSheet("border: 0px solid white");

    //button
    acceptbutton->setMinimumWidth(170);
    acceptbutton->setMinimumHeight(40);
	acceptbutton->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 white, stop: 1 grey);"
		"border-style: solid;"
		"border-width: 1px;"
		"border-color: black;"
		"border-radius: 15px;}"));

    //fonts
    namelabel->setFont(dialogfont);
    namebox->setFont(dialogfont);
    sizelabel->setFont(dialogfont);
    skilllabel->setFont(dialogfont);
    texlabel->setFont(dialogfont);
    sizeoptions->setFont(dialogfont);
    skilloptions->setFont(dialogfont);
    texoptions->setFont(dialogfont);
    acceptbutton->setFont(dialogfont);

    //sliders
    sizeslider->setOrientation(Qt::Horizontal);
    sizeslider->setSliderPosition(sizechoice);
    sizeslider->setTickPosition(QSlider::TicksAbove);
    sizeslider->setTickInterval(1);
    sizeslider->setRange(1, 4);
    sizeslider->setMinimumWidth(250);
	sizeslider->setStyleSheet("border: 0px solid white");

    skillslider->setOrientation(Qt::Horizontal);
    skillslider->setSliderPosition(skillchoice);
    skillslider->setTickPosition(QSlider::TicksAbove);
    skillslider->setTickInterval(1);
    skillslider->setRange(1, 3);
    skillslider->TicksAbove;
    skillslider->setMinimumWidth(250);
	skillslider->setStyleSheet("border: 0px solid white");

    texslider->setOrientation(Qt::Horizontal);
    texslider->setSliderPosition(texchoice);
    texslider->setTickPosition(QSlider::TicksAbove);
    texslider->setTickInterval(1);
    texslider->setRange(1, 3);
    texslider->TicksAbove;
    texslider->setMinimumWidth(250);
	texslider->setStyleSheet("border: 0px solid white");

    //pixmap
    textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertexture150x125.png"));
	textcubeimg->setStyleSheet("border: 0px solid white");

    //horizontal layouts
    usernamelayout->addWidget(namelabel);
    usernamelayout->addWidget(namebox, 2);

    sizelayout->addWidget(sizelabel);
    sizelayout->addWidget(sizeoptions);

    skilllayout->addWidget(skilllabel);
    skilllayout->addWidget(skilloptions);

    texlayout->addWidget(texlabel);
    texlayout->addWidget(texoptions);

    //assets added to grid layout
    gridlayout->addLayout(usernamelayout, 1, 1, 1, 1, Qt::AlignLeading);

    gridlayout->addLayout(sizelayout, 3, 1, 1, 1, Qt::AlignLeft);
    gridlayout->addWidget(sizeslider, 4, 1, 1, 2, Qt::AlignLeft);

    gridlayout->addLayout(skilllayout, 5, 1, 1, 1, Qt::AlignLeft);
    gridlayout->addWidget(skillslider, 6, 1, 1, 2, Qt::AlignLeft);

    gridlayout->addLayout(texlayout, 7, 1, 1, 1, Qt::AlignLeft);
    gridlayout->addWidget(texslider, 8, 1, 1, 2, Qt::AlignLeft);

    gridlayout->addWidget(textcubeimg, 8, 4, 2, 2, Qt::AlignRight);

    gridlayout->addWidget(acceptbutton, 9, 1, 1, 2, Qt::AlignCenter);

    //slots
    QObject::connect(acceptbutton, SIGNAL(clicked()), this, SLOT(acceptbuttonClicked()));
    QObject::connect(sizeslider, SIGNAL(valueChanged(int)), this, SLOT(sizesliderValueChanged(int)));
    QObject::connect(namebox, SIGNAL(textEdited(QString)), this, SLOT(enterplayernameTextEdited(const QString)));
    QObject::connect(texslider, SIGNAL(valueChanged(int)), this, SLOT(texsliderValueChanged(int)));
    QObject::connect(skillslider, SIGNAL(valueChanged(int)), this, SLOT(skillsliderValueChanged(int)));
}

void Dialog::sizesliderValueChanged(int value){

    if (value == 1) {
        this->sizeoptions->setText("Small");
    }
    if (value == 2) {
        this->sizeoptions->setText("Medium");
    }
    if (value == 3) {
        this->sizeoptions->setText("Large");
    }
    if (value == 4) {
        this->sizeoptions->setText("XLarge");
    }

    sizechoice = value;
}

void Dialog::skillsliderValueChanged(int value){

    if (value == 1) {
        skilloptions->setText("Shrink & Boost");
    }
    if (value == 2) {
        skilloptions->setText("Gravity Gun");
    }
    if (value == 3) {
        skilloptions->setText("Tron");
    }

    skillchoice = value;
}

void Dialog::texsliderValueChanged(int value){

    if(value == 1){
    this->texoptions->setText("Checker");
    textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertexture150x125.png"));
    }

    if(value == 2){
    this->texoptions->setText("Something1");
    textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertexturepink150x125.png"));
    }

    if(value == 3){
    this->texoptions->setText("Something2");
    textcubeimg->setPixmap(QPixmap("../../Qt/icons/checkertextureblue150x125.png"));
    }

    texchoice = value;
}

void Dialog::enterplayernameTextEdited(const QString &arg1){
    //save player input as qstring
    playername = arg1;

    //convert qstring playername to string
    Dialog::qstringtostring(playername);
}

void Dialog::acceptbuttonClicked(){

    MainWindow sendinguserdata;

    sendinguserdata.grabuserdata(sizechoice, skillchoice, texchoice, playerusername);

    this->close();

    //reset namebox
    playerusername = "Player1";
}

Dialog::~Dialog()
{
    delete ui;

 //   delete gridlayout;
 //   delete usernamelayout;
 //   delete sizelayout;
 //   delete skilllayout;
 //   delete texlayout;

    delete namebox;

    delete namelabel;
    delete sizelabel;
    delete skilllabel;
    delete texlabel;

    delete sizeoptions;
    delete skilloptions;
    delete texoptions;

    delete textcubeimg;

    delete acceptbutton;

    delete sizeslider;
    delete skillslider;
    delete texslider;
}
