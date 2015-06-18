/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GTreasure.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef GTREASURE_H
#define GTREASURE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Treasure;
class MazeField;
class MazeCard;

/**
 * @brief The GTreasure class graficka reprezentacia pokladu
 */
class GTreasure : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  GTreasure(MazeField *mf, QGraphicsItem *parent = nullptr);
  GTreasure(MazeCard *mc, QGraphicsItem *parent = nullptr);

  void repaint();
private:
  MazeField *m_mazeField = nullptr;
  MazeCard *m_mazeCard = nullptr;
};

#endif // GTREASURE_H
