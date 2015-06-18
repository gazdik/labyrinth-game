/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MainWindow.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include <QCloseEvent>

#include "GMazeBoard.h"
#include "GFreeCard.h"
#include "GCardPack.h"
#include "GNewGameDialog.h"

#include "Game.h"

#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setWindowTitle("Labyrinth");

  initWindow();

  // Ziskaj farebnu paletu lcd panelu zobrazujuceho skore
  m_scorePalleteDefault = ui->player1score->palette();

  // Nastav farebnu paletu aktualnemu hracovi
  m_scorePalleteCurrent = ui->player2score->palette();
}

MainWindow::~MainWindow()
{
  delete ui;

  // Zmaz hru
  if (m_game) {
    delete m_game;
  }
}

void MainWindow::on_actionNewGame_triggered()
{
  // Ak uz je rozohrata nejaka hra, ziskaj potrvdenie
  if (m_game) {
    if (exitMessageBox() == false) {
      return;
    }
  }

  GNewGameDialog *param = new GNewGameDialog(this);
  // Zobraz dialogove okno novej hry, ak ho uzivatel zatvori, skonci
  if (!param->exec())
    return;

  // Zmaz instanciu starej hry
  if (m_game) {
    delete m_game;
    m_game = nullptr;
  }

  // Vytvor instanciu novej hry zo zadanych parametrov
  m_game = new Game(param->m_players, param->m_size, param->m_treasures);

  initWindow();
  showWindow();
}

void MainWindow::showStatusMsg(Game::STATUS status)
{
  if (status == Game::STATUS::WRONG_POSITION)
    statusBar()->showMessage("Wrong instert position!", 2000);
  else if (status == Game::STATUS::INSERT_FIRST)
    statusBar()->showMessage("Insert card first!", 2000);
  else if (status == Game::STATUS::WRONG_MOVE)
    statusBar()->showMessage("NO WAY!", 2000);
  else if (status == Game::STATUS::OLDEST_CHANGE)
    statusBar()->showMessage("Already oldest change!", 2000);
  else if (status == Game::STATUS::GAME_OVER) {
    m_boardScene->setGameOver();

    statusBar()->showMessage("Game over!");
    // Deaktivuj ovladacie prvky
    ui->okButton->setDisabled(true);
    ui->turnRightButton->setDisabled(true);
  }
}

void MainWindow::boardCard_clicked(int n)
{
  Game::STATUS status = m_game->moveOrInsert(n / m_game->m_mazeBoard->size(),
                                             n % m_game->m_mazeBoard->size());

  showStatusMsg(status);

  repaint();
}

void MainWindow::on_actionHelp_triggered()
{
  QFile file(":/text/help.txt");
  file.open(QIODevice::ReadOnly|QIODevice::Text);

  QString msg(file.readAll());

  QMessageBox::about(this, "Help", msg);
}

void MainWindow::repaint()
{
  m_boardScene->repaint();
  m_freeCardScene->repaint();
  m_cardPackScene->repaint(m_game->m_currPlayer);

  // Obnov skore hracov
  ui->player1score->display(m_game->m_players[0]->score());
  ui->player2score->display(m_game->m_players[1]->score());
  if (m_game->numPlayers() >= 3) {
    ui->player3score->display(m_game->m_players[2]->score());
  }
  if (m_game->numPlayers() >= 4) {
    ui->player4score->display(m_game->m_players[3]->score());
  }

  // Obnov standardnu farebnu paletu hracom
  ui->player1score->setPalette(m_scorePalleteDefault);
  ui->player2score->setPalette(m_scorePalleteDefault);
  ui->player3score->setPalette(m_scorePalleteDefault);
  ui->player4score->setPalette(m_scorePalleteDefault);

  // Zmen farbu aktualnemu hracovi
  switch (m_game->m_currPlayer->number()) {
    case 0:
      ui->player1score->setPalette(m_scorePalleteCurrent);
      break;
    case 1:
      ui->player2score->setPalette(m_scorePalleteCurrent);
      break;
    case 2:
      ui->player3score->setPalette(m_scorePalleteCurrent);
      break;
    case 3:
      ui->player4score->setPalette(m_scorePalleteCurrent);
      break;
    default:
      throw std::runtime_error("Wrong number of players.");
      break;
  }
}

void MainWindow::showWindow()
{
  // Zobraz hraciu dosku
  m_boardScene = new GMazeBoard(m_game->m_mazeBoard, this);
  connect(m_boardScene, SIGNAL(clicked(int)), SLOT(boardCard_clicked(int)));

  ui->boardView->setScene(m_boardScene);
  ui->boardView->show();

  // Zobraz volnu kartu
  m_freeCardScene = new GFreeCard(m_game->m_mazeBoard, this);
  ui->freeCardView->setScene(m_freeCardScene);
  ui->freeCardView->show();

  // Zobraz tlacidlo pre otocenie volnej karty
  ui->turnRightButton->show();
  ui->turnRightButton->setEnabled(true);

  // Zobraz tlacidlo pre undo
  ui->okButton->show();
  ui->okButton->setEnabled(true);

  // Zobrazenie balicku s kartami
  m_cardPackScene = new GCardPack(m_game->m_currPlayer, this);
  ui->cardPackView->setScene(m_cardPackScene);
  ui->cardPackView->show();

  // Zobraz skore panel
  ui->player1label->show();
  ui->player1score->show();
  ui->player2score->show();
  ui->player2label->show();
  if (m_game->numPlayers() >= 3) {
    ui->player3label->show();
    ui->player3score->show();
  }
  if (m_game->numPlayers() >= 4) {
    ui->player4label->show();
    ui->player4score->show();
  }

  // Zobraz tlacidlo ulozenia hry
  ui->actionSaveGame->setEnabled(true);

  repaint();
}

void MainWindow::on_actionAbout_triggered()
{
  QFile file(":/text/about.txt");
  file.open(QIODevice::ReadOnly|QIODevice::Text);

  QString msg(file.readAll());

  QMessageBox::about(this, "About", msg);
}

void MainWindow::on_turnRightButton_clicked()
{
  m_game->rotateCard();
  repaint();
}

void MainWindow::on_okButton_clicked()
{
  Game::STATUS status = m_game->nextTurn();

  showStatusMsg(status);

  repaint();
}

bool MainWindow::exitMessageBox()
{
  QMessageBox msgBox(this);

  msgBox.setWindowTitle("Labyrinth");
  msgBox.setText("Are you sure you want to close current game?");
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Cancel);

  int clicked = msgBox.exec();

  bool retVal = false;

  switch (clicked) {
    case QMessageBox::Yes:
      retVal = true;
      break;
    case QMessageBox::Cancel:
      retVal = false;
      break;
    default:
      // Nenastane
      break;
  }

  return retVal;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (m_game == nullptr)
    event->accept();
  else {
    if (exitMessageBox())
      event->accept();
    else
      event->ignore();
  }
}

void MainWindow::on_actionLoadGame_triggered()
{
  // Ak je rozohrata hra, vyziadaj potrvdenie
  if (m_game) {
    if (exitMessageBox() == false) {
        return;
    }
  }

  // Ziskaj cestu k suboru
  QString path = QFileDialog::getOpenFileName(this, "Load Game", ".",
                                      "Game Files (*.game);;Any Files(*)");

  // Ak uzivatel nevybral subor, skonci
  if (path.isNull())
    return;

  // Odstran aktualnu hru, ak existuje
  if (m_game) {
    delete m_game;
    m_game = nullptr;
  }

  // Vytvor instanciu hry
  m_game = new Game(path.toStdString());

  // Inicializuj a zobraz okno
  initWindow();
  showWindow();
}

void MainWindow::on_actionSaveGame_triggered()
{
  // Ziskaj cestu k suboru
  QString path = QFileDialog::getSaveFileName(this, "Save Game", ".",
                                              "Game Files (*.game);;All Files (*)");

  // Ak uzivatel nevybral subor, skonci
  if (path.isNull())
    return;

  m_game->saveGame(path.toStdString());
}

void MainWindow::initWindow()
{
  ui->boardView->hide();
  ui->freeCardView->hide();
  ui->cardPackView->hide();
  ui->turnRightButton->hide();
  ui->okButton->hide();
  ui->player1label->hide();
  ui->player1score->hide();
  ui->player2label->hide();
  ui->player2score->hide();
  ui->player3label->hide();
  ui->player3score->hide();
  ui->player4label->hide();
  ui->player4score->hide();
  ui->actionSaveGame->setDisabled(true);
}


void MainWindow::on_actionQuit_triggered()
{
  close();
}
