/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file TreasureCard.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#ifndef TREASURECARD_H
#define TREASURECARD_H

#include "Treasure.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

/**
 * @brief The TreasureCard class reprezentuje jednu hraciu kartu. Karta
 * zobrazuje poklad (instanciu triedy Treasure)
 */
class TreasureCard {
private:
  /**
   * @brief TreasureCard len kvoli serializacii
   */
  TreasureCard() {}

public:
  /**
   * @brief TreasureCard inicializuje kartu, nastavenie zobrazeneho pokladu tr
   * @param tr ukazatel na objekt tr
   */
  TreasureCard(Treasure *tr);

  /**
   * @brief treasure Ziska ukazovatel na poklad
   * @return ukazovatel na poklad
   */
  Treasure *treasure();

  /**
   * @brief ~TreasureCard vykonava destrukciu objektu TreasureCard.
   */
  bool operator==(TreasureCard const &rhs) const;
  bool operator!=(TreasureCard const &rhs) const;

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_treasure;
  }

  /**
   * @brief treasure objekt pokladu
   */
  Treasure m_treasure;
};

#endif // TREASURECARD_H
