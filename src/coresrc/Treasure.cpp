/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file Treasure.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include "Treasure.h"
using namespace std;

vector<Treasure> Treasure::m_treasures;

Treasure::Treasure(int code)
{
   m_myCode = code;
}

void Treasure::createSet()
{
  if (m_treasures.empty()) {
    for (int i = 0; i < m_nTreasures; i++)
      m_treasures.push_back(Treasure{i});
  }
}

void Treasure::deleteSet()
{
  m_treasures.clear();
}

Treasure *Treasure::getTreasure(int code)
{
  if (code < 0 || code >= static_cast<int>(m_treasures.size()))
    return nullptr;

  return &m_treasures[code];
}

int Treasure::getType()
{
  return m_myCode;
}

bool Treasure::operator==(Treasure const &rhs) const
{
  return this->m_myCode == rhs.m_myCode;
}

bool Treasure::operator!=(Treasure const &rhs) const {
  return !(*this == rhs);
}
