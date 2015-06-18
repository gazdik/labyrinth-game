/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file Game.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "Game.h"

#include <stdexcept>
#include <algorithm>
#include <fstream>

using namespace std;


Game::Game(int numPlayers, int boardSize, int numTreasures)
  : m_numPlayers {numPlayers}
{
  // Vytvorenie balicka kariet
  m_cardPack = new CardPack(numTreasures, numTreasures);

  // Vytvorenie hracej dosky a vygenerovanie novej hry
  m_mazeBoard = new MazeBoard;
  m_mazeBoard->createMazeBoard(boardSize);
  m_mazeBoard->newGame(m_cardPack);

  for (int i=0; i < numPlayers; i++) {
    // Uloz hraca
    m_players.push_back(new Player(i));
    switch (i) {
      case 0:
        m_mazeBoard->get(0, 0).getCard()->setPlayer(m_players[i]);
        break;
      case 1:
        m_mazeBoard->get(boardSize-1, boardSize-1).getCard()->setPlayer(m_players[i]);
        break;
      case 2:
        m_mazeBoard->get(0, boardSize-1).getCard()->setPlayer(m_players[i]);
        break;
      case 3:
        m_mazeBoard->get(boardSize-1, 0).getCard()->setPlayer(m_players[i]);
        break;
      default:
        throw runtime_error("Wrong number of players.");
        break;
    }
  }

  // Nastav prveho hraca ako aktualneho hraca
  m_currPlayer = m_players[0];

  // Zamiesaj balicek
  m_cardPack->shuffle();

  // Potiahni kartu prvemu hracovi
  m_currPlayer->setTreasure(m_cardPack->popCard());

  // Nastav stav hry
  m_mode = MODE::INSERTING;
}

Game::Game(string path)
{
  // Input file stream
  ifstream ifs (path);

  // Boost input archive for deserialization
  boost::archive::binary_iarchive ia(ifs);

  // Deserialize object m_game from archive
  ia >> *this;
}

Game::~Game()
{
  for (auto x: m_players)
    delete x;

  delete m_mazeBoard;
  delete m_cardPack;
}

Game::STATUS Game::moveOrInsert(int row, int col)
{
  STATUS status;

  // Ak sa hra nachadza v stave vkladania karty
  if (m_mode == MODE::INSERTING) {
    MazeField mf(row, col);
    if (m_mazeBoard->shift(mf)) {
      m_mode = MODE::MOVING;
      status = STATUS::OK;
    } else {
      status = STATUS::WRONG_POSITION;
    }
  }
  // Ak sa hra nachadza v stave kedy sa posuva hrac
  else if (m_mode == MODE::MOVING) {
    MazeField *fieldPlayer = nullptr;
    MazeField *fieldClicked = &m_mazeBoard->get(row, col);

    int rowPlayer = 0;
    int colPlayer = 0;

    // Najdi hraca na hracej doske
    for (int i =0; i < m_mazeBoard->size() * m_mazeBoard->size(); i++) {
      // 2D index do hracej dosky
      rowPlayer = i / m_mazeBoard->size();
      colPlayer = i % m_mazeBoard->size();

      fieldPlayer = &m_mazeBoard->get(rowPlayer, colPlayer);
      if (fieldPlayer->getCard()->getPlayer() == m_currPlayer)
        break;
    }

    /*
     * Zmen poziciu hraca na zaklade zadanych suradnic
     */

    // Posun vlavo, ak je to mozne
    if ((rowPlayer - row == 0) && (colPlayer - col == 1)) {
      if (fieldPlayer->getCard()->canGo(MazeCard::CANGO::LEFT) &&
          fieldClicked->getCard()->canGo(MazeCard::CANGO::RIGHT)) {
        // Posun hraca
        swap(fieldPlayer->getCard()->m_player, fieldClicked->getCard()->m_player);
      }
      status = STATUS::OK;
    }
    // Pusun hore, ak je to mozne
    else if ((rowPlayer - row == 1) && (colPlayer - col == 0)) {
      if (fieldPlayer->getCard()->canGo(MazeCard::CANGO::UP) &&
          fieldClicked->getCard()->canGo(MazeCard::CANGO::DOWN)) {
        // Posun hraca
        swap(fieldPlayer->getCard()->m_player, fieldClicked->getCard()->m_player);
      }
      status = STATUS::OK;
    }
    // Pusun vpravo, ak je to mozne
    else if ((rowPlayer - row == 0) && (colPlayer - col == -1)) {
      if (fieldPlayer->getCard()->canGo(MazeCard::CANGO::RIGHT) &&
          fieldClicked->getCard()->canGo(MazeCard::CANGO::LEFT)) {
        // Posun hraca
        swap(fieldPlayer->getCard()->m_player, fieldClicked->getCard()->m_player);
      }
      status = STATUS::OK;
    }
    // Posun dole, ak je to mozne
    else if ((rowPlayer - row == -1) && (colPlayer - col == 0)) {
      if (fieldPlayer->getCard()->canGo(MazeCard::CANGO::DOWN) &&
          fieldClicked->getCard()->canGo(MazeCard::CANGO::UP)) {
        // Posun hraca
        swap(fieldPlayer->getCard()->m_player, fieldClicked->getCard()->m_player);
      }
      status = STATUS::OK;
    }
    else {
      status = STATUS::WRONG_MOVE;
    }
  }
  else {
    status = STATUS::GAME_OVER;
  }

  return status;
}


Game::STATUS Game::nextTurn()
{
  STATUS status;

  if (m_mode == MODE::MOVING) {
    // Otestovanie, ci hrac nasiel kartu
    MazeField *fieldPlayer = nullptr;

    // Najdi hraca na hracej doske
    for (int i =0; i < m_mazeBoard->size() * m_mazeBoard->size(); i++) {
      // 2D index do hracej dosky
      int rowPlayer = i / m_mazeBoard->size();
      int colPlayer = i % m_mazeBoard->size();

      fieldPlayer = &m_mazeBoard->get(rowPlayer, colPlayer);
      if (fieldPlayer->getCard()->getPlayer() == m_currPlayer)
        break;
    }

    // Otestuj, ci je na policku karta
    if (fieldPlayer->getTreasure()) {
      if (*fieldPlayer->getTreasure() == *m_currPlayer->getTreasure()) {
        m_currPlayer->incrementScore();
        fieldPlayer->getCard()->clearTreasure();
        m_currPlayer->setTreasure(nullptr);

        // Ak hrac dosiahol skore potrebne pre vyhru, ukonci hru
        if (m_currPlayer->score() >= (m_cardPack->initSize() / m_numPlayers)) {
          m_mode = MODE::GAMEOVER;
          return STATUS::GAME_OVER;
        }
      }
    }

    // Posun hru na dalsieho hraca
    m_currPlayer = m_players[(m_currPlayer->number() + 1) % m_numPlayers];

    // Ak nasledujuci hrac nema kartu, potiahnutie novej karty
    if (m_currPlayer->getTreasure() == nullptr) {
      m_currPlayer->setTreasure(m_cardPack->popCard());

    }

    // Zmen stav hry
    m_mode = MODE::INSERTING;

    status = STATUS::OK;
  } else {
    status = STATUS::INSERT_FIRST;
  }

  return status;
}

void Game::rotateCard()
{
  m_mazeBoard->getFreeCard().turnRight();
}

bool Game::saveGame(string path)
{
  // Output file stream
  ofstream ofs (path);

  // Boost output archive for serialization
  boost::archive::binary_oarchive oa(ofs);

  // Serialize object m_game to output archive
  oa << *this;

  return true;
}

int Game::numPlayers()
{
  return m_numPlayers;
}

Player *Game::winner()
{
  // Return value
  Player *winner = nullptr;

  if (m_mode == MODE::GAMEOVER) {
    // Najdi hraca s najvyssim skore
    int maxScore = 0;
    for (int i = 0; i < m_numPlayers; i++) {
      if (m_players[i]->score() > maxScore) {
        winner = m_players[i];
        maxScore = winner->score();
      }
    }
  } else {
    // Ak hra neskoncila
    winner = nullptr;
  }

  return winner;
}

