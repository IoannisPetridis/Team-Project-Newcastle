#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <Qt\include\QtWidgets\qmainwindow.h>
//#include <Qt\include\QtCore\qstring.h>

#include "..\..\Qt\include\QtWidgets\qmainwindow.h"
#include "dialog.h"
#include "..\..\Qt\include\QtCore\qstring.h"
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   //player stats (initialised to 1 in .cpp in case chara creation is skipped)
   static int playersize;
   static int playerskill;
   static int playertexture;
   static std::string playername;

   //grabs data from dialog (chara creation) window
   void grabuserdata(int size, int skill, int tex, std::string name) {
      playersize = size;
      playerskill = skill;
      playertexture = tex;
      playername = name;
   }

   //returns data
   int returnuserdata() {
       return playersize;
       return playerskill;
       return playertexture;
   }

   //returns username
   std::string returnusername() {
	   return playername;
   }

   //slots are actions
private slots:
    void on_actionCreate_Character_triggered();

    void on_createcharabutton_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
