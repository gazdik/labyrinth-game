/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GTreasure.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GTreasure.h"

#include "Treasure.h"
#include "MazeField.h"
#include <QString>

GTreasure::GTreasure(MazeField *mf, QGraphicsItem *parent)
  : QGraphicsPixmapItem {parent}, m_mazeField {mf}
{
  repaint();
}

GTreasure::GTreasure(MazeCard *mc, QGraphicsItem *parent)
  : QGraphicsPixmapItem {parent}, m_mazeCard {mc}
{
  repaint();
}

void GTreasure::repaint()
{
  // Schovaj pixmapu
  hide();

  TreasureCard *treasureCard;

  if (m_mazeField != nullptr) {
    treasureCard = m_mazeField->getTreasure();
  } else {
    treasureCard = m_mazeCard->getTreasure();
  }

  if (treasureCard == nullptr) {
    return;
  }

  int treasureType = treasureCard->treasure()->getType();

  QString file = QString(":/img/treasure%1.png").arg(treasureType);

  setPixmap(QPixmap(file));
  setZValue(-5);

  // Zobraz pixmapu
  show();
}
