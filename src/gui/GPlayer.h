/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GPlayer.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef GPLAYER_H
#define GPLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>

class MazeField;

/**
 * @brief The GPlayer class graficka reprezentacia hraca
 */
class GPlayer : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  // constructors
  GPlayer(MazeField *field, QGraphicsItem *parent = nullptr);

  // public methods
  void repaint();

private:
  MazeField *m_mazeField;
};

#endif // GPLAYER_H
