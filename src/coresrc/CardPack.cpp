/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file CardPack.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include "CardPack.h"
#include <stdexcept>
#include <random>
#include <algorithm>
#include <chrono>


using namespace std;

CardPack::CardPack(int maxSize, int initSize)
  : m_size {maxSize}, m_initSize {initSize}
{
  if (initSize > maxSize)
    throw runtime_error("CardPack: initSize < maxSize");

  Treasure::createSet();

  for(int i=initSize-1; i >= 0; i--) {
    m_cards.push_back(new TreasureCard{Treasure::getTreasure(i)});
  }
}

CardPack::~CardPack()
{
  for (auto x : m_cards)
    delete x;

  Treasure::deleteSet();
}

TreasureCard* CardPack::popCard()
{
  --m_size;
  return m_cards[m_size];
}

TreasureCard* CardPack::at(int i)
{
  return m_cards[i];
}

int CardPack::size()
{
  return m_size;
}

int CardPack::initSize()
{
  return m_initSize;
}

void CardPack::shuffle()
{
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();

  std::shuffle (m_cards.begin(), m_cards.end(), default_random_engine(seed));
}
