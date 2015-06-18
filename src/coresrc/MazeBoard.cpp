/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MazeBoard.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include "MazeBoard.h"

#include "CardPack.h"

#include <cstdlib>
#include <ctime>

using namespace std;

void MazeBoard::createMazeBoard(int n)
{
  m_size = n;
  createFields();
}

void MazeBoard::newGame(CardPack *cardPack)
{
  // Nahodne generovany typ, rotacia, index do dosky
  int iType, iRotate, iIndex;
  srand(time(NULL));

  /*
   * Generovanie ciest na dosku
   */

  for (int r=0; r < m_size; r++) {
    for (int c=0; c < m_size; c++) {
      // Nahodne vygenerovanie rotacii a typov
      iRotate = rand() % 4;
      iType = rand() % 3;

      // Docasna karta
      MazeCard tmp;

      /*
       * Natocenie kariet podla umiestnenia
       */

      // Lavy horny roh
      if ((r == 0) && (c == 0)) {
        tmp.set(MazeCard::TYPE::C);
        // Otoc o 180 stupnov
        tmp.turnRight(); tmp.turnRight();
      }
      // Pravy horny roh
      else if ((r == 0) && (c == m_size - 1)) {
        tmp.set(MazeCard::TYPE::C);
        // Otoc o 270 stupnov
        tmp.turnRight(); tmp.turnRight(); tmp.turnRight();
      }
      // Pravy dolny roh
      else if ((r == m_size - 1) && (c == m_size - 1)) {
        tmp.set(MazeCard::TYPE::C);
      }
      // Lavy dolny roh
      else if ((r == m_size -1) && (c == 0)) {
        tmp.set(MazeCard::TYPE::C);
        // Otoc o 90 stupnov
        tmp.turnRight();
      }
      // Parny riadok a stlpec
      else if ((r % 2 == 0) && (c % 2 == 0)) {
        // Cesta v tvare T
        tmp.set(MazeCard::TYPE::F);

        // Umiestnenie v hornom riadku
        if (r == 0) {
          // Otoc o 180 stupnov
          tmp.turnRight(); tmp.turnRight();
        }
        // Umiestnenie v lavom stlpci
        else if (c == 0) {
          // Otoc o 90 stupnov
          tmp.turnRight();
        }
        // Umiestnenie v dolnom riadku
        else if (r == m_size -1) {
          // neotacaj
        }
        // Umiestnenie v pravom stlpci
        else if (c == m_size -1) {
          // Otoc o 270 stupnov
          tmp.turnRight(); tmp.turnRight(); tmp.turnRight();
        }
        // Umiestnenie v strede dosky
        else {
          // Otoc nahodne
          for (int i=0; i < iRotate; i++)
            tmp.turnRight();
        }
      }
      // Pozicia s nahodnou cestou a natocenim
      else {
        tmp.set(static_cast<MazeCard::TYPE>(iType));
        for (int i=0; i < iRotate; i++)
          tmp.turnRight();
      }

      // Umiestni kartu na dosku
      m_fields[getIndex(r, c)].putCard(tmp);
    }
  }

  // Vygeneruj volnu kartu
  iType = rand() % 3;
  m_freeCard.set(static_cast<MazeCard::TYPE>(iType));

  /*
   * Umiestnenie pokladov na dosku
   */

  for (int i=0; i < cardPack->size(); i++) {
    while (true) {
      // Ziskaj nahodny index do dosky
      iIndex = rand() % (m_size * m_size);

      // Preved ho na 2D index
      int row = iIndex / m_size;
      int col = iIndex % m_size;

      // Ziskaj kartu
      MazeCard *currentCard = m_fields[iIndex].getCard();

      // Ak sa index nachadza na rohoch, generuj novy index
      if ((row == 0 && col == 0) ||
          (row == 0 && col == m_size -1) ||
          (row == m_size - 1 && col == m_size - 1) ||
          (row == m_size -1 && col == 0)) {
        continue;
      }

      // Ak sa umiestnenie karty nepodari, generuj novy index
      if (currentCard->setTreasure(cardPack->at(i)) == false)
        continue;
      else
        break;
    }
  }

  /*
   * Nastavenie premennej obsahujucu poziciu na ktoru bola v predoslom
   * tahu vkladana karta
   */

  m_forbiddenPos = &get(0,0);
}

MazeField &MazeBoard::get(int r, int c)
{
  return m_fields[getIndex(r, c)];
}

MazeCard &MazeBoard::getFreeCard()
{
  return m_freeCard;
}

bool MazeBoard::shift(MazeField &mf)
{
  int row = mf.row();
  int col = mf.col();

  bool retVal;

  // Otestuj, ci na opacnu poziciu nebolo vkladane v predchadzajucom tahu
  if (m_forbiddenPos->col() == col && m_forbiddenPos->row() == row)
    return false;

  MazeCard tmp = m_freeCard;
  // indexujeme policka na hracej doske od 0

  // prvy riadok [0, c] - kamene sa posunu dole v stlpci c, ak je c sude
  if (row == 0 && (col % 2) != 0) {
    m_freeCard = *m_fields[getIndex(m_size - 1, col)].getCard();
    m_forbiddenPos = &get(m_size - 1, col);

    // Ak je na vysunutej karte hrac, vloz ho na vkladanu kartu
    if (m_freeCard.getPlayer()) {
      tmp.setPlayer(m_freeCard.getPlayer());
      m_freeCard.setPlayer(nullptr);
    }

    for (int i = m_size - 2; i >= 0; i--) {
      m_fields[getIndex(i + 1, col)].putCard(*m_fields[getIndex(i, col)].getCard());
    }
    m_fields[getIndex(row, col)].putCard(tmp);

    retVal = true;
  }

  // posledny riadok [n, c] - kamene sa posunu nahor v stlpci c, ak je c sude
  else if (row == m_size -1 && (col % 2) != 0) {
    m_freeCard = *m_fields[getIndex(0, col)].getCard();
    m_forbiddenPos = &get(0, col);

    // Ak je na vysunutej karte hrac, vloz ho na vkladanu kartu
    if (m_freeCard.getPlayer()) {
      tmp.setPlayer(m_freeCard.getPlayer());
      m_freeCard.setPlayer(nullptr);
    }

   for (int i = 1; i < m_size; i++) {
      m_fields[getIndex(i - 1, col)].putCard(*m_fields[getIndex(i, col)].getCard());
    }
    m_fields[getIndex(row, col)].putCard(tmp);

    retVal = true;
  }

  // prvy stlpec [r, 0] - kamene sa posunu doprava na riadku r, ak je r sude
  else if ((row % 2) != 0 && col == 0) {
    m_freeCard = *m_fields[getIndex(row, m_size-1)].getCard();
    m_forbiddenPos = &get(row, m_size - 1);

    // Ak je na vysunutej karte hrac, vloz ho na vkladanu kartu
    if (m_freeCard.getPlayer()) {
      tmp.setPlayer(m_freeCard.getPlayer());
      m_freeCard.setPlayer(nullptr);
    }

   for (int i = m_size-2; i >= 0; i--) {
      m_fields[getIndex(row, i+1)].putCard(*m_fields[getIndex(row, i)].getCard());
    }
    m_fields[getIndex(row, col)].putCard(tmp);

    retVal = true;
  }

  // posledny stlpec [r, c] - kamene sa posunu dolava na riadku r, ak je r sude
  else if ((row % 2) != 0 && col == m_size - 1)
  {
    m_freeCard = *m_fields[getIndex(row, 0)].getCard();
    m_forbiddenPos = &get(row, 0);

    // Ak je na vysunutej karte hrac, vloz ho na vkladanu kartu
    if (m_freeCard.getPlayer()) {
      tmp.setPlayer(m_freeCard.getPlayer());
      m_freeCard.setPlayer(nullptr);
    }

   for (int i = 1; i < m_size; i++) {
      m_fields[getIndex(row, i-1)].putCard(*m_fields[getIndex(row, i)].getCard());
    }
    m_fields[getIndex(row, col)].putCard(tmp);

    retVal = true;
  } else {
    retVal = false;
  }

  return retVal;
}

int MazeBoard::size()
{
  return m_size;
}

void MazeBoard::createFields()
{
  for (int i=0; i < m_size; i++) {
    for (int j=0; j < m_size; j++) {
      m_fields.push_back(MazeField{i, j});
    }
  }
}

int MazeBoard::getIndex(int row, int col)
{
  return row * m_size + col;
}

