/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MazeBoard.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#ifndef MAZEBOARD_H
#define MAZEBOARD_H

#include "MazeField.h"
#include "MazeCard.h"

#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>


class CardPack;

/**
 * @brief The MazeBoard class Reprezentuje hraciu hosku. Doska je rozdelena na
 * policka (MazeField) a je stvorcova o rozmere n. Umoznuje generovat novu hru
 * a posunovat kamene na riadkoch a stlpcoch.
 */
class MazeBoard
{
public:
  /**
   * @brief createMazeBoard Vytvori hraciu plochu o velkosti n. Pri
   * inicializacii sa vytvoria policka (instancie triedy MazeField) a
   * umiestnia sa na spravne pozicie. Kamene sa nevytvaraju, vznika len
   * prazdna hracia plocha.
   * @param n Velkost hracej plochy
   */
  void createMazeBoard(int n);

  /**
   * @brief newGame Vytvori novu hru. Generuje hracie kamene a umiestnuje ich
   * na policka. Sucasne vygeneruje jeden volny kamen, ktory uchovava mimo
   * policka.
   */
  void newGame(CardPack *cardPack);

  /**
   * @brief get Vracia policko na pozicii [r, c]. V pripade chyby (mimo rozsah)
   * vracia null.
   * @param r riadok
   * @param c stlpec
   * @return ukazovatel na policko
   */
  MazeField &get(int r, int c);

  /**
   * @brief getFreeCard Vracia volny kamen. Ak taky kamen neexistuje (hra
   * nebola vytvorena), vracia null.
   * @return ukazovatel na volny kamen.
   */
  MazeCard &getFreeCard();

  /**
   * @brief shift Vykona vlozenie volneho kamena na poziciu policka mf. Podla
   * pozicie policka mf sa vykona prislusne posunutie kamenov:
   * - prvy riadok [0, c] - kamene sa posunu dole v stlpci c, ak je c sude
   * - posledny riadok [n, c] - kamene sa posunu nahor v stlpci c, ak je c sude
   * - prvy stlpec [r, 0] - kamene sa posunu doprava na riadku r, ak je r sude
   * - posledny stlpec [r, c] - kamene sa posunu dolava na riadku r, ak je r sude
   *
   * Na policko mf sa vlozi volny kamen a dalsie kamene sa posunu. Kamen, ktory
   * tymto postupem vysunut, sa stava volnym kamenem.
   * Ak policko mf nesplnuje vyssie uvedenne podmienky, nerobi metoda nic.
   * @param mf volny kamen (MazeField)
   */
  bool shift(MazeField &mf);

  /**
   * @brief size vracia velkost dosky
   * @return velkost dosky
   */
  int size();
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_size;
    ar & m_fields;
    ar & m_freeCard;
    ar & m_forbiddenPos;
  }

  int m_size;
  std::vector<MazeField> m_fields;
  MazeCard m_freeCard;
  MazeField* m_forbiddenPos = nullptr;

  /**
   * @brief getIndex ziska 1D index z 2D suradnic
   */
  int getIndex(int row, int col);

  /**
   * @brief createFields vytvori policka hracej dosky
   */
  void createFields();
};
#endif // MAZEBOARD_H
