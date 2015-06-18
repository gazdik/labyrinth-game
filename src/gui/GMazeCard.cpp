/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GMazeCard.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GMazeCard.h"
#include "MazeField.h"
#include "MazeCard.h"


GMazeCard::GMazeCard(MazeField *field, QGraphicsItem *parent)
  : QGraphicsPixmapItem(parent), m_mazeField {field}
{
  setAcceptHoverEvents(true);

  repaint();
}

GMazeCard::GMazeCard(MazeCard *card, QGraphicsItem *parent)
  : QGraphicsPixmapItem(parent), m_mazeCard {card}
{
  repaint();
}


void GMazeCard::repaint()
{
  MazeCard *card;

  if(m_mazeField)
    card = m_mazeField->getCard();
  else
    card = m_mazeCard;

  QPixmap pixmap;

  switch (card->type()) {
    case MazeCard::TYPE::C:
      pixmap.load(":/img/C.png");
      break;
    case MazeCard::TYPE::L:
      pixmap.load(":/img/L.png");
      break;
    case MazeCard::TYPE::F:
      pixmap.load(":/img/F.png");
      break;
    default:
      break;
  }

  setPixmap(pixmap);
  setTransformOriginPoint(pixmap.width()/2, pixmap.height()/2);
  setRotation(card->rotation());

  setZValue(-10);
}

void GMazeCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
  emit clicked();
}

void GMazeCard::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  event->accept();
  setOpacity(0.8);
}

void GMazeCard::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  event->accept();
  setOpacity(1.0);
}
