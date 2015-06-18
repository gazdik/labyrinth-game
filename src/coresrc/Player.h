/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file Player.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H

#include "TreasureCard.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

/**
 * @brief The Player class reprezentuje jednoho hraca
 */
class Player
{
public:
  friend class Game;
  /**
   * @brief Player vytvori instanciu hraca a nastavi mu jeho cislo
   * @param num cislo hraca
   */
  Player(int num);

  /**
   * @brief addScore pripocita skore hracovi
   * @param score hodnota skore
   */
  void incrementScore();

  /**
   * @brief setTreasure nastavi poklad, ktory hrac hlada
   * @param treasure karta s pokladom
   */
  void setTreasure(TreasureCard *treasure);

  /**
   * @brief getTreasure vrati kartu pokladu, ktory hrac hlada
   * @return treasure karta s pokladom
   */
  TreasureCard* getTreasure();

  /**
   * @brief score vrati skore hraca
   * @return skore
   */
  int score();

  /**
   * @brief number vrati cislo hraca
   * @return cislo hraca
   */
  int number();
protected:
  Player() {}
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_number;
    ar & m_score;
    ar & m_treasure;
  }

  int m_number;
  int m_score;
  TreasureCard *m_treasure = nullptr;
};

#endif // PLAYER_H
