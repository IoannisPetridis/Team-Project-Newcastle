#include "GeneratedFiles\ui_mainwindow.h"

#include "dialog.h"
#include "mainwindow.h"
#include "../../ncltech/ActionHandler.h"
#include <iostream>

//stats are initially set to 1 in case creation window is not opened
int MainWindow::playersize = 1;
int MainWindow::playerskill = 1;
int MainWindow::playertexture = 1;
std::string MainWindow::playername = "Player1";

//window choices (start as main menu so false0
bool MainWindow::AIchoice = false;
bool MainWindow::isExitWindow = false;
bool MainWindow::isPauseWindow = false;
bool MainWindow::isStartWindow = false;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	//hides toolbar
	ui->mainToolBar->hide();

	//sets vertical layout as main widget (centred)
	centralwidget = new QWidget(this);
	this->setCentralWidget(centralwidget);
	vertlayout = new QVBoxLayout(centralwidget);
	vertlayout->setAlignment(Qt::AlignCenter);

	title->setAlignment(Qt::AlignCenter);
	title->setPixmap(QPixmap("../../Qt/icons/cubeofduty2.png"));
	title->setContentsMargins(0, 0, 0, 30);

	//IF THE END GAME SCREEN HAS BEEN TRIGGERED
	if (isExitWindow){
		title->setPixmap(QPixmap("../../Qt/icons/gameover.png"));
		playbutton->setText("Play Again");
		createbutton->hide();
		AIbutton->hide();
		exitbutton->setText("Quit");
	}

	//IF THE PAUSE SCREEN HAS BEEN TRIGGERED
	if (isPauseWindow){
		title->setPixmap(QPixmap("../../Qt/icons/paused.png"));
		playbutton->setText("Continue");
		createbutton->hide();
		AIbutton->hide();
		exitbutton->setText("Quit?");
	}

	//IF THE START MENU HAS BEEN CALLED
	if (isStartWindow){
		title->setPixmap(QPixmap("../../Qt/icons/begingame.png"));
		playbutton->setText("START");
		createbutton->hide();
		AIbutton->hide();
		exitbutton->hide();
	}

	//buttton style sheets
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

	//button font
    QFont buttonfont("Lucida Console", 14);
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
    vertlayout->addWidget(title, 0, Qt::AlignCenter);
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
	delete AIbutton;
    delete exitbutton;
}

//this is called when play button clicked
void MainWindow::play_game(){ 
	Audio::AddSound({ 0.0f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel7, Audio::ButtonSelect, 5);
	this->close();

	if (isExitWindow){
		ActionHandler::Instance()->ResetGame();
		isExitWindow = false;
		ActionHandler::Instance()->GameOver = false;
	}

	if (isPauseWindow){
		Window::GetWindow().ShowOSPointer(false);
		isPauseWindow = false;
	}

	if (isStartWindow){
		Window::GetWindow().ShowOSPointer(false);
		isStartWindow = false;
	}
}

//called when exit button clicked
void MainWindow::exit_now(){
	Audio::AddSound({ 0.0f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel7, Audio::ButtonSelect, 5);

	if (isPauseWindow){
		isPauseWindow = false;
	}

    this->close();
	exit(0);
}

//called when ai button clicked
void MainWindow::make_ai(){
	Audio::AddSound({ 0.0f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel7, Audio::ButtonSelect, 5);
	if (!AIchoice){
		AIbutton->setText("Three AI Mode");
		AIchoice = true;
	}

	else {
		AIbutton->setText("Single AI Mode");
		AIchoice = false;
	}
}

//called when create character button clicked
void MainWindow::create_chara_triggered(){
   
	Audio::AddSound({ 0.0f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel7, Audio::ButtonSelect, 5);
   Dialog mDialog;
   mDialog.setModal(true);
   mDialog.setWindowTitle("Character Creation");
   mDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
   mDialog.setMinimumSize(480, 400);
   mDialog.setStyleSheet("border: 5px solid grey");

   //finds primary screen height and width
   QScreen *screen = QGuiApplication::primaryScreen();
   QRect screensize = screen->availableGeometry();
   int centreX = (screensize.width() - mDialog.width()) / 2.f;
   int centreY = (screensize.height() - mDialog.height()) / 2.f;

   //sets window to centre of screen
   QPoint screencoords;
   screencoords.setX(centreX);
   screencoords.setY(centreY);
   mDialog.move(screencoords);

   mDialog.exec();

}
