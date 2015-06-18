/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MazeField.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#ifndef MAZEFIELD_H
#define MAZEFIELD_H

#include "Treasure.h"
#include "MazeCard.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>


/**
 * @brief The MazeField class reprezentuje policko na hracej doske.
 * Kazde policko je identifikovane poziciou [row, col]
 */
class MazeField
{
public:
  /**
   * @brief MazeField ...
   * @param row index riadku (1...n)
   * @param col index stlpca (1...n)
   */
  MazeField(int row, int col);

  /**
   * @brief row Vracia cislo riadku, na ktorom je policko umiestnene na hracej
   * doske
   * @return Cislo riadku
   */
  int row();

  /**
   * @brief col Vracia cislo stlpca, na ktorom je policko umiestnene na hracej
   * doske
   * @return Cislo stlpca
   */
  int col();

  /**
   * @brief getCard Vracia hraci kamen, ktory je umiestneny na policku.
   * Ak na policku ziadny kamen nie je, vracia null
   * @return Ukazovatel na hraci kamen
   */
  MazeCard* getCard();
  /**
   * @brief getTreasure ziska poklad leziaci na karte policka
   * @return ukazovatel na poklad
   */
  TreasureCard* getTreasure();

  /**
   * @brief putCard Vlozi hraci kamen na policko
   * @param c Hraci kamen
   */
  void putCard(MazeCard &c);

private:
  MazeField() {}
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & r;
    ar & c;
    ar & m_card;
  }

  int r;
  int c;
  MazeCard m_card;
};

#endif // MAZEFIELD_H
