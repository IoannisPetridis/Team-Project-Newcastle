#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "..\..\Qt\include\QtWidgets\qmainwindow.h"
#include "..\..\Qt\include\QtCore\qstring.h"
#include "..\..\Qt\include\QtWidgets\qvboxlayout"
#include "..\..\Qt\include\QtWidgets\qpushbutton.h"
#include "..\..\Qt\include\QtWidgets\qlabel.h"
#include "..\..\Qt\include\QtWidgets\qwidget.h"
#include "..\..\Qt\include\QtWidgets\qsizepolicy.h"
#include "..\..\Qt\include\QtGui\qscreen.h"
#include "..\..\Qt\include\QtWidgets\qgraphicseffect.h"
#include "..\..\ncltech\Audio.h"
#include "..\..\Qt\include\QtGui\qpainter.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //layouts
    QWidget *centralwidget;
    QVBoxLayout *vertlayout;

    //creates title and buttons
	QLabel *title = new QLabel;
    QPushButton *playbutton = new QPushButton("Play");
    QPushButton *createbutton = new QPushButton("Create Character");
	QPushButton*AIbutton = new QPushButton("AI toggle");
    QPushButton *exitbutton = new QPushButton("Exit");

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //player stats (initialised to 1 in .cpp in case chara creation is skipped)
    static int playersize;
    static int playerskill;
    static int playertexture;
    static std::string playername;
	static bool AIchoice;
	static bool isExitWindow;
	static bool isPauseWindow;

    //grabs data from dialog (chara creation) window
    void grabuserdata(int size, int skill, int tex, std::string name) {
        playersize = size;
        playerskill = skill;
        playertexture = tex;
        playername = name;
    }

    //stats getter
    int returnuserdata() {
        return playersize;
        return playerskill;
        return playertexture;
    }

    //username getter
    std::string returnusername() {
        return playername;
    }

public slots:
    void play_game();
    void create_chara_triggered();
    void exit_now();
	void make_ai();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
