/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file main.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include <iostream>

#include "MainWindow.h"
#include <QApplication>


using namespace std;
int main(int argc, char *argv[])
{

  QApplication app {argc, argv};
  MainWindow w;

  w.show();

  return app.exec();
}


