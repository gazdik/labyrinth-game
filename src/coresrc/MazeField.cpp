/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MazeField.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include "MazeField.h"

MazeField::MazeField(int row, int col) : r{row}, c{col} {}

int MazeField::row()
{
  return r;
}

int MazeField::col()
{
  return c;
}

MazeCard *MazeField::getCard()
{
  return &m_card;
}

TreasureCard *MazeField::getTreasure()
{
  return m_card.getTreasure();
}

void MazeField::putCard(MazeCard &c)
{
  m_card = c;
}
