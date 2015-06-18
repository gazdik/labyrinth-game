/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file TreasureCard.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include "TreasureCard.h"

TreasureCard::TreasureCard(Treasure *tr) : m_treasure{*tr} {}

Treasure *TreasureCard::treasure()
{
  return &m_treasure;
}

bool TreasureCard::operator==(TreasureCard const& rhs) const
{
  return this->m_treasure == rhs.m_treasure;
}

bool TreasureCard::operator!=(TreasureCard const& rhs) const
{
  return !(*this == rhs);
}

