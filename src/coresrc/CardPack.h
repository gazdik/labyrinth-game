/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file CardPack.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef CARDPACK_H
#define CARDPACK_H

#include "TreasureCard.h"
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>


/**
 * @brief The CardPack class reprezentuje balicek hracich kariet (instancie
 * triedy TreasureCard).
 */
class CardPack {
  friend class StoreCommand;
protected:
  /**
   * @brief CardPack defaultny konstruktor kvoli serializacii
   */
  CardPack () {}
public:
  /**
   * @brief CardPack inicializuje balicek parametrami 'maxSize'  a 'initSize'.
   * Musi platit, ze maxSize >= initSize. Naplni balicek kartami, ktore vytvori.
   * Karty su v balicky usporiadane vzostupne podla kodu pokladu (vrchna karta
   * reprezentuje poklad s kodom 0, dalsia karta poklad s kodom 1 atd.)
   * @param maxSize maximaly pocet kariet v balicku
   * @param initSize pociatocny pocet kariet v balicku
   */
  CardPack(int maxSize, int initSize);

  ~CardPack();

  /**
   * @brief popCard vyjme vrchnu kartu z balicku a vrati ju (pocet kariet v
   * balicku sa znizi.
   * @return objekt TreasureCard
   */
  TreasureCard *popCard();

  /**
   * @brief at vrati kartu na zadanej pozicii v balicku
   * @param i pozicia karty v balicku
   * @return objekt TreasureCard
   */
  TreasureCard *at(int i);

  /**
   * @brief size vracia aktualny pocet kariet v balicku
   * @return pocet kariet v balicku
   */
  int size();

  /**
   * @brief initSize vracia velkost balicka pri inicializacii
   * @return velkost
   */
  int initSize();

  /**
   * @brief shuffle zamiecha kartami. Po tejto operacii sa zmeni usporiadanie
   * kariet v balicku. (V jave je mozne pozit triedu java.util.Random, t.j.
   * v C++ bude urcito nieco podobne)
   */
  void shuffle();

  /**
   * @brief ~CardPack vykona destrukciu objektu CardPack.
   */
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_cards;
    ar & m_size;
    ar & m_initSize;
  }

  /**
   * @brief m_cards uchovava vsetky objekty reprezentujuce karty
   */
  std::vector<TreasureCard *> m_cards;

  /**
   * @brief m_size pocet kariet v balicku
   */
  int m_size;

  /**
   * @brief m_initSize velkost pri inicializacii
   */
  int m_initSize;
};

#endif // CARDPACK_H
