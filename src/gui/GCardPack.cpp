/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GCardPack.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GCardPack.h"

#include "TreasureCard.h"
#include "Player.h"

#include <stdexcept>

#include <QGraphicsPixmapItem>


GCardPack::GCardPack(TreasureCard *tr, QObject *parent)
  : QGraphicsScene {parent}
{
  m_sceneItem = new QGraphicsPixmapItem;
  addItem(m_sceneItem);
  repaint(tr);
}

GCardPack::GCardPack(Player *player, QObject *parent)
  : QGraphicsScene {parent}
{
  m_sceneItem = new QGraphicsPixmapItem;
  addItem(m_sceneItem);
  repaint(player);
}

GCardPack::~GCardPack()
{
  delete m_sceneItem;
}

void GCardPack::repaint(TreasureCard *tr)
{
  if (tr == nullptr) {
    return;
  }

  int treasureType = tr->treasure()->getType();

  QString file = QString(":/img/trasure_card%1.png").arg(treasureType);

  QPixmap pixmap(file);
  m_sceneItem->setPixmap(pixmap);
}

void GCardPack::repaint(Player *player)
{
  TreasureCard *tr = player->getTreasure();
  repaint(tr);
}
