#include "GeneratedFiles\ui_mainwindow.h"

#include "dialog.h"
#include "mainwindow.h"
#include <iostream>

//stats are initially set to 1 in case creation window is not opened
int MainWindow::playersize = 1;
int MainWindow::playerskill = 1;
int MainWindow::playertexture = 1;
std::string MainWindow::playername = "Player1";
bool MainWindow::WannaExit = false;
bool MainWindow::AIchoice = false;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	//hides toolbar
	ui->mainToolBar->hide();

	//sets vertical layout as main widget (centred)
	centralwidget = new QWidget(this);
	this->setCentralWidget(centralwidget);
	vertlayout = new QVBoxLayout(centralwidget);
	vertlayout->setAlignment(Qt::AlignCenter);

	//sets fonts for title & buttons
	QFont font("CordiaUPC", 50, QFont::Bold);
	title->setFont(font);
	title->setAlignment(Qt::AlignCenter);
	title->setText("<font color='white'>Rocket League V2.0</font>");

	playbutton->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 white, stop: 1 grey);"
		"border-style: solid;"
		"border-width: 2px;"
		"border-color: black;"
		"border-radius: 15px;}"));

	createbutton->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 white, stop: 1 grey);"
		"border-style: solid;"
		"border-width: 2px;"
		"border-color: black;"
		"border-radius: 15px;}"));

	exitbutton->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 white, stop: 1 grey);"
		"border-style: solid;"
		"border-width: 2px;"
		"border-color: black;"
		"border-radius: 15px;}"));

	AIbutton->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 white, stop: 1 grey);"
		"border-style: solid;"
		"border-width: 2px;"
		"border-color: black;"
		"border-radius: 15px;}"));

    QFont buttonfont("CordiaUPC", 18);
    playbutton->setFont(buttonfont);
    createbutton->setFont(buttonfont);
    exitbutton->setFont(buttonfont);
	AIbutton->setFont(buttonfont);

    //button sizes
    playbutton->setMinimumSize(200, 40);
    playbutton->setMaximumSize(200, 40);
    createbutton->setMinimumSize(200, 40);
    createbutton->setMaximumSize(200, 40);
    exitbutton->setMinimumSize(200, 40);
    exitbutton->setMaximumSize(200, 40);
	AIbutton->setMinimumSize(200, 40);
	AIbutton->setMaximumSize(200, 40);

    //adds assets to the vertical layout
    vertlayout->addWidget(title, Qt::AlignCenter);
    vertlayout->addWidget(playbutton, 0, Qt::AlignCenter);
    vertlayout->addWidget(createbutton, 0, Qt::AlignCenter);
	vertlayout->addWidget(AIbutton, 0, Qt::AlignCenter);
    vertlayout->addWidget(exitbutton, 0, Qt::AlignCenter);

    //its slots time
    QObject::connect(playbutton, SIGNAL(clicked()), this, SLOT(play_game()));
    QObject::connect(createbutton, SIGNAL(clicked()), this, SLOT(create_chara_triggered()));
    QObject::connect(exitbutton, SIGNAL(clicked()), this, SLOT(exit_now()));
	QObject::connect(AIbutton, SIGNAL(clicked()), this, SLOT(make_ai()));
}

MainWindow::~MainWindow()
{
    delete ui;

    //delete centralwidget
    //delete vertlayout

    delete title;
    delete playbutton;
    delete createbutton;
    delete exitbutton;
}

void MainWindow::play_game(){
    this->close();
}

void MainWindow::exit_now(){
    WannaExit = true;
    this->close();
}

void MainWindow::make_ai(){
	if (!AIchoice){
		AIbutton->setText("Three AI Mode");
		AIchoice = true;
	}

	else {
		AIbutton->setText("Single AI Mode");
		AIchoice = false;
	}
}

void MainWindow::create_chara_triggered(){

   Dialog mDialog;
   mDialog.setModal(true);
   //mDialog.setWindowIcon(QIcon("../../Qt/Icons/sicklogo.bmp"));
   mDialog.setWindowTitle("Character Creation");
   mDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
   mDialog.setMinimumSize(480, 400);
   mDialog.setStyleSheet("border: 5px solid grey");

   //finds primary screen height and width
   QScreen *screen = QGuiApplication::primaryScreen();
   QRect screensize = screen->availableGeometry();
   int centreX = (screensize.width() - mDialog.width()) / 2.f;
   int centreY = (screensize.height() - mDialog.height()) / 2.f;

   //sets qt window to centre of screen
   QPoint screencoords;
   screencoords.setX(centreX);
   screencoords.setY(centreY);
   mDialog.move(screencoords);

   mDialog.exec();

}
