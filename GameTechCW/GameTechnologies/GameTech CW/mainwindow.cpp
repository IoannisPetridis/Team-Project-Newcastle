#include "mainwindow.h"
#include "GeneratedFiles/ui_mainwindow.h"
#include "dialog.h"
#include <iostream>

//stats are initially set to 1 in case creation window is not opened
int MainWindow::playersize = 1;
int MainWindow::playerskill = 1;
int MainWindow::playertexture = 1;
std::string MainWindow::playername = "Player1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->mainToolBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//creates the chara creation window when the button is triggered/clicked
void MainWindow::on_actionCreate_Character_triggered()
{
    //modal version (cant interact)
   Dialog mDialog;
   mDialog.setModal(true);
   mDialog.setWindowIcon(QIcon("../../Qt/Icons/sicklogo.bmp"));
   mDialog.setWindowTitle("Character Creation");
   mDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
   mDialog.exec();
}

void MainWindow::on_createcharabutton_clicked()
{
    Dialog mDialog;
    mDialog.setModal(true);
	mDialog.setWindowIcon(QIcon("../../Qt/Icons/sicklogo.bmp"));
	mDialog.setWindowTitle("Character Creation");
	mDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    mDialog.exec();
}