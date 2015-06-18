/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MazeCard.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#ifndef MAZECARD_H
#define MAZECARD_H

#include <string>
#include <array>
#include <algorithm>
#include <exception>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "TreasureCard.h"
#include "Player.h"

/**
 * @brief The MazeCard class reprezentuje jeden kamen, ktory sa umiestuje
 * na policka hracej plochy. Kamen uchovava informaciu o ceste, t.j. o smeroch,
 * kade je mozne kamen opustit
 */
class MazeCard
{
public:
  friend class Game;

  MazeCard();

  /**
   * @brief The TYPE enum reprezentuje typ kamena
   */
  enum class TYPE {C, L, F};

  /**
   * @brief The CANGO enum vnoreny vyctovy typ. Definuje styri hodnoty
   * reprezentujuce smer, kade je mozne kamen opustit.
   */
  enum class CANGO {LEFT, UP, RIGHT, DOWN};

  /**
   * @brief set nastavi typ kamena 'type'
   * @param type reprezentuje typ kamena, moze byt:
   * "C" - kamen reprezentujuci rohovu cestu (v tvare pismena L).
   * Po inicializacii smeruje cesta zlava nahor.
   * "L" - kamen reprezentujuci rovnu cestu. Po inicializacii smeruje
   * cesta zlava doprava.
   * "F" - vytvori kamen reprezentujuci rozdelenie cesty (v tvare pismena T).
   * Po inicializacii smeruje cesta zlava nahor a doprava.
   */
  void set(TYPE type);

   /**
   * @brief canGo Vracia informaciu, ci je mozne opustit kamen danym smerom
   * @param dir smer z vyctoveho typu CANGO
   * @return 'true', ak je mozne opustit kamen danym smerom, inak 'false'
   */
  bool canGo(CANGO dir);

  /**
   * @brief turnRight otoci kamen o 90° doprava
   */
  void turnRight();

  /**
   * @brief type vrati typ aktualnej karty
   * @return typ
   */
  TYPE type();

  /**
   * @brief rotation vrati pootocenie aktualnej karty
   * @return pootocenie v stupnoch
   */
  int rotation();

  /**
   * @brief setTreasure nastavi poklad na policko hracej dosky
   * @param treasureCard ukazovatel na objekt karty z balicku
   * @return true, ak na karte este nebola ziadna karta, inak false
   */
  bool setTreasure(TreasureCard *treasureCard);

  /**
   * @brief getTreasure vrati poklad na karte
   * @return ukazovatel na kartu pokladu
   */
  TreasureCard *getTreasure();

  /**
   * @brief setPlayer umiestni na kartu hraca
   * @param player ukazovatel na hraca
   */
  void setPlayer(Player *player);

  /**
   * @brief getPlayer vrati ukazovatel na hraca, inak NULL
   * @return ukazovatel na hraca alebo NULL
   */
  Player *getPlayer();

  bool operator==(MazeCard const &rhs) const;

  bool operator!=(MazeCard const &rhs) const;

  void clearTreasure();
  TreasureCard *getTreasureCard() const;
  void setTreasureCard(TreasureCard *treasureCard);

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_dirs;
    ar & m_type;
    ar & m_rotation;
    ar & m_treasureCard;
    ar & m_player;
  }

  /**
   * @brief m_dirs pole reprezentujuce smery, ktorymi je mozne kamen opustit.
   * dirs[0] - LEFT
   * dirs[1] - UP
   * dirs[2] - RIGHT
   * dirs[3] - DOWN
   */
  std::vector<bool> m_dirs;

  /**
   * @brief m_type uchovava typ karty
   */
  TYPE m_type;
  /**
   * @brief m_rotation uchovava aktualna rotaciu karty v stupnoch
   */
  int m_rotation;

  /**
   * @brief m_treasureCard karta s pokladom
   */
  TreasureCard *m_treasureCard = nullptr;

protected:
  /**
   * @brief m_player ukazavatel na hraca
   */
  Player *m_player = nullptr;
};

#endif // MAZECARD_H
