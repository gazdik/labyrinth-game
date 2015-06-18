/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MainWindow.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QPushButton>
#include <vector>
#include "Game.h"


class QStandardItemModel;
class QStandardItem;
class QGraphicsView;
class QGraphicsScene;
class GMazeBoard;
class GFreeCard;
class GCardPack;
class QMessageBox;

namespace Ui {
  class MainWindow;
}

/**
 * @brief The MainWindow class hlavne okno s rozlozenim hry a ovladacimi prvkami
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

signals:

private slots:
  void on_actionNewGame_triggered();

  void boardCard_clicked(int n);

  void on_actionAbout_triggered();

  void on_actionHelp_triggered();

  void on_turnRightButton_clicked();

  void on_okButton_clicked();
  
  void on_actionLoadGame_triggered();

  void on_actionSaveGame_triggered();

  void on_actionQuit_triggered();

private:
  // Private methods
  /**
   * @brief Znovu vykresli vsetky graficke elementy po zmene
   */
  void repaint();

  /**
   * @brief showStatusMsg zobrazi na status bare spravu na zaklade stavu z hry
   * @param status stav o ktorom ma byt zobrazena sprava
   */
  void showStatusMsg(Game::STATUS status);

  /**
   * @brief showWindow zobrazi vsetky prvky main window
   */
  void showWindow();

  /**
   * @brief initWindow zinicializuje vsetky prvky main window
   */
  void initWindow();

  bool exitMessageBox();

  void closeEvent(QCloseEvent *event);

  /**
   * @brief m_game Instancia hry
   */
  Game *m_game = nullptr;

  Ui::MainWindow *ui;

  GMazeBoard *m_boardScene = nullptr;
  GFreeCard *m_freeCardScene = nullptr;
  GCardPack *m_cardPackScene = nullptr;

  QPalette m_scorePalleteDefault;
  QPalette m_scorePalleteCurrent;
  QMessageBox *m_helpDialog;
  QMessageBox *m_aboutDialog;
};


#endif // MAINWINDOW_H
