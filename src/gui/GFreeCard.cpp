/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GFreeCard.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GFreeCard.h"

#include "GMazeCard.h"
#include "GTreasure.h"

#include "MazeBoard.h"


GFreeCard::GFreeCard(MazeBoard *mb, QObject *parent)
  : QGraphicsScene {parent}, m_mazeBoard {mb}
{
  MazeCard *freeCard = &m_mazeBoard->getFreeCard();

  m_mazeCardItem = new GMazeCard(freeCard);
  m_treasureItem = new GTreasure(freeCard);

  addItem(m_mazeCardItem);
  addItem(m_treasureItem);
}

GFreeCard::~GFreeCard()
{
  delete m_mazeCardItem;
  delete m_treasureItem;
}

void GFreeCard::repaint()
{
  m_mazeCardItem->repaint();
  m_treasureItem->repaint();
}
