/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GFreeCard.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef GFREECARD_H
#define GFREECARD_H

#include <QGraphicsScene>

class MazeBoard;
class GMazeCard;
class GTreasure;

/**
 * @brief The GFreeCard class graficka reprezentacia volnej karty
 */
class GFreeCard : public QGraphicsScene
{
  Q_OBJECT
public:
  GFreeCard(MazeBoard* mb, QObject *parent = nullptr);
  ~GFreeCard();

  // public methods
  void repaint();

private:
  // private variables
  MazeBoard *m_mazeBoard; /* hracia doska */
  GMazeCard *m_mazeCardItem; /* graf. reprezent. karty */
  GTreasure *m_treasureItem; /* graf. reprezent. karty */
};

#endif // GFREECARD_H
