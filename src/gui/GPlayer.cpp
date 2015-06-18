/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GPlayer.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GPlayer.h"

#include "MazeField.h"
#include <QString>

GPlayer::GPlayer(MazeField *field, QGraphicsItem *parent)
  : QGraphicsPixmapItem {parent}, m_mazeField {field}
{
  repaint();
}

void GPlayer::repaint()
{
  // Schovaj pixmapu
  hide();

  Player *player = m_mazeField->getCard()->getPlayer();
  if (player == nullptr)
    return;

  int playerNum = player->number();

  QString file = QString(":/img/player%1.png").arg(playerNum);

  setPixmap(QPixmap(file));
  setZValue(0);

  // Zobraz pixmapu
  show();
}
