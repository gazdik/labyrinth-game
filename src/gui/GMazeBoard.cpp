/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GMazeBoard.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GMazeBoard.h"

#include "MazeBoard.h"
#include "GMazeCard.h"
#include "GTreasure.h"
#include "GPlayer.h"

#include <QSignalMapper>

GMazeBoard::GMazeBoard(MazeBoard *mb, QObject *parent)
  : QGraphicsScene(parent), m_mazeBoard {mb}
{
  m_signalMapper = new QSignalMapper(this);
  connect(m_signalMapper, SIGNAL(mapped(int)), this, SIGNAL(clicked(int)));

  setBoard();
}

GMazeBoard::~GMazeBoard()
{
  for(auto x : m_cardItems)
    delete x;

  for(auto x : m_treasureItems)
    delete x;

  for(auto x : m_playerItems)
    delete x;
}

void GMazeBoard::repaint()
{
  for (int i = 0; i < m_mazeBoard->size() * m_mazeBoard->size(); i++) {
    m_cardItems[i]->repaint();
    m_treasureItems[i]->repaint();
    m_playerItems[i]->repaint();
  }
}

void GMazeBoard::setGameOver()
{
  QPixmap pixmap(":/img/youwin.png");

  QGraphicsPixmapItem *item =  new QGraphicsPixmapItem(pixmap);

  item->setZValue(10);
  item->setPos((width() - pixmap.width()) / 2,
               (height() - pixmap.height()) / 2);

  addItem(item);
}

void GMazeBoard::setBoard()
{
  for (int row = 0; row < m_mazeBoard->size(); row++) {
    for (int col = 0; col < m_mazeBoard->size(); col++) {
      // 1D index do dosky
      int iIndex = row * m_mazeBoard->size() + col;

      // Ziskaj policko dosky
      MazeField &mf = m_mazeBoard->get(row, col);

      // Vypocitaj poziciu na doske
      QPoint position {col * 80, row * 80};

      // Vytvor novy objekt cesty
      GMazeCard *sCard = new GMazeCard(&mf);
      m_cardItems.push_back(sCard);

      // Nastav poziciu cesty
      sCard->setPos(position);
      addItem(sCard);

      // Vytvor novy objekt pokladu
      GTreasure *treasureItem = new GTreasure(&mf);
      m_treasureItems.push_back(treasureItem);
      treasureItem->setPos(position);
      addItem(treasureItem);

      // Vytvor novy object hraca
      GPlayer *playerItem = new GPlayer(&mf);
      m_playerItems.push_back(playerItem);
      playerItem->setPos(position);
      addItem(playerItem);

      // Namapuj signal stlacenia mysi nad objektom cesty
      connect(sCard, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
      m_signalMapper->setMapping(sCard, iIndex);
    }
  }
}
