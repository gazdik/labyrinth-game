/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GMazeCard.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef BOARDCARD_H
#define BOARDCARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class MazeField;
class MazeCard;

/**
 * @brief The GMazeCard class graficka reprezentacia policka na hracej doske
 */
class GMazeCard : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
  // constructors
  GMazeCard(MazeField *field, QGraphicsItem *parent = nullptr);
  GMazeCard(MazeCard *card, QGraphicsItem *parent = nullptr);

  // public methods
  void repaint();

  // public methods (events)
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
  void clicked();

private:
  // private variables
  MazeField *m_mazeField = nullptr;
  MazeCard *m_mazeCard = nullptr;

};

#endif // BOARDCARD_H
