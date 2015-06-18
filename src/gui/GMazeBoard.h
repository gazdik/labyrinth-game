/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GMazeBoard.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QGraphicsScene>
#include <QVector>

class QSignalMapper;
class MazeBoard;
class GMazeCard;
class GTreasure;
class GPlayer;

/**
 * @brief The GMazeBoard class graficka reprezentacia hracej dosky
 */
class GMazeBoard : public QGraphicsScene
{
  Q_OBJECT
public:
  GMazeBoard(MazeBoard* mb, QObject *parent = nullptr);
  ~GMazeBoard();

  // public methods
  void repaint();

  void setGameOver();

signals:
  void clicked(int n);

private:
  // private variables
  QSignalMapper *m_signalMapper = nullptr;
  MazeBoard *m_mazeBoard;
  QVector<GMazeCard *> m_cardItems;
  QVector<GTreasure *> m_treasureItems;
  QVector<GPlayer *> m_playerItems;

  // private methods
  void setBoard();

};

#endif // BOARDSCENE_H
