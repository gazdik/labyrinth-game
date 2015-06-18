/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file Game.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "MazeBoard.h"
#include "CardPack.h"
#include "Player.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <vector>
#include <string>

/**
 * @brief The Game class logika hry
 */
class Game
{
public:
  friend class StoreCommand;
  // public methods

  /**
   * @brief Game vytvori hru o zadanych parametroch
   * @param players pocet hracov
   * @param boardSize velkost hracej dosky
   * @param treasures pocet pokladov
   */
  Game(int numPlayers, int boardSize, int numTreasures);

  /**
   * @brief Game vytvori instanciu hry zo zadaneho suboru
   * @param path cesta k suboru
   */
  Game (std::string path);
  Game() {}

  ~Game();

  /**
   * @brief The STATUS enum informuje o uspesnosti vykonania nejakej akcie
   */
  enum class STATUS {
    OK,
    INSERTED,
    MOVED,
    WRONG_MOVE,
    WRONG_POSITION,
    INSERT_FIRST,
    OLDEST_CHANGE,
    GAME_OVER,
  };

  /**
   * @brief moveOrInsert posunie hraca na konkretne policko, resp. vlozi
   * na zadane policko volnu kartu na zaklade stavu hry
   * @param row riadok
   * @param col stlpec
   * @return true, ak sa posun podaril, false ak bol tah nepovoleny
   */
  STATUS moveOrInsert(int row, int col);
  /**
   * @brief nextTurn potvrdi hracov tah a zmeni tah na dalsieho hraca
   * @return true, ak bolo potrvdenie uspesne
   */
  STATUS nextTurn();
  /**
   * @brief rotateCard otoci volnu kartu vpravo
   */
  void rotateCard();

  /**
   * @brief saveGame ulozi hru do suboru zadaneho cestou
   * @param path cesta k suboru
   * @return true, ak bol zapis uspesny
   */
  bool saveGame(std::string path);

  /**
   * @brief numPlayers vrati aktualny pocet hracov
   * @return pocet hracov
   */
  int numPlayers();

  Player *winner();

  // public variables

  /**
   * @brief m_mazeBoard instancia hracej dosky
   */
  MazeBoard *m_mazeBoard;

  /**
   * @brief m_players instancie hracov
   */
  std::vector<Player *> m_players;

  /**
   * @brief currPlayer hrac na tahu
   */
  Player *m_currPlayer;

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_mazeBoard;
    ar & m_players;
    ar & m_currPlayer;
    ar & m_mode;
    ar & m_numPlayers;
    ar & m_cardPack;
  }

  /**
   * @brief The MODE enum stav v ktorom sa hra momentalne nachadza
   */
  enum class MODE { INSERTING, MOVING, GAMEOVER };

  /**
   * @brief m_mode mod hry
   */
  MODE m_mode;
  /**
   * @brief m_numPlayers pocet hracov
   */
  int m_numPlayers;

  /**
   * @brief m_cardPack instancia hracieho balicku
   */
  CardPack *m_cardPack;
};


#endif // GAME_H
