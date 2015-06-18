/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GCardPack.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef GCARDPACK_H
#define GCARDPACK_H

#include <QGraphicsScene>

class TreasureCard;
class Player;
class QGraphicsPixmapItem;

/**
 * @brief The GCardPack class graficka reprezentacia balicku kariet
 */
class GCardPack : public QGraphicsScene
{
    Q_OBJECT
public:
  // constructors
  GCardPack(TreasureCard *cp, QObject *parent = nullptr);
  GCardPack(Player *player, QObject *parent = nullptr);
  ~GCardPack();

  // public methods
  void repaint(TreasureCard *tr);
  void repaint(Player *player);
private:
  // private variables
  QGraphicsPixmapItem *m_sceneItem = nullptr;
};

#endif // GCARDPACK_H
