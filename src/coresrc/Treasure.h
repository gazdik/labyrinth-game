/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file Treasure.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#ifndef TREASURE_H
#define TREASURE_H

#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

/**
 * @brief The Treasure class reprezentuje jeden poklad. Kazdy poklad
 * je identifikovany svojim kodom. Kody sa prideluju vzostupne od
 * hodnoty 0. Kazdy objekt triedy Treasure je nemenny. Trieda obsahuje
 * na statickej urovni pole uchovavajuce vygenerovany set pokladov,
 * dalej sa pouzivaju objekty z tohoto setu (vid getTreasure()).
 */
class Treasure {
public:
  friend class TreasureCard;
  /**
   * @brief createSet vytvori set pokladov, ktore je mozne potom pouzivat.
   * Pocet vytvorenych objektov je urceny vnutornou premennou, ktora je
   * nastavena na hodnotu 24.
   */
  static void createSet();

  /**
   * @brief deleteSet odstrani pred tym vytvoreny set pokladov. Ak set
   * pokladov nebol vytvoreny, nerobi nic.
   * Pozn.: Pravdepodobne nebude potrebny
   */
  static void deleteSet();

  /**
   * @brief getTreasure Z vytvoreneho setu vracia objekt pokladu odpovedajuceho
   * zadanemu kodu 'code'. Ak taky objekt neexistuje, vracia null.
   * @param code kod pokladu
   * @return ukazatel na objekt Treasure
   */
  static Treasure* getTreasure(int code);

  int getType();

  bool operator==(Treasure const &rhs) const;
  bool operator!=(Treasure const &rhs) const;

protected:
  Treasure() {}

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & m_myCode;
  }

  /**
   * @brief Treasure inicializuje objekt, nastavi jeho kod 'code'.
   * @param code cislo identifikujuce poklad. Zacinaju od nuly.
   */
  Treasure(int code);

  /**
   * @brief mycode kod pokladu
   */
  int m_myCode;
  /**
   * @brief treasures uchovava vsetky objekty reprezentujuce poklady
   */
  static std::vector<Treasure> m_treasures;

  /**
   * @brief m_nTreasures pocet pokladov
   */
  static const int m_nTreasures = 24;
};

#endif // TREASURE_H
