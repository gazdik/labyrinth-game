/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file MazeCard.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 ************************************************************************** */

#include "MazeCard.h"
#include <stdexcept>

using namespace std;

// C++11 inicializacia
MazeCard::MazeCard()
  : m_dirs {false, false, false, false}, m_type {TYPE::C}, m_rotation {0}
{
}

void MazeCard::set(TYPE type)
{
  switch (type) {
    case TYPE::C:
      m_dirs = {true, true, false, false};
      m_type = type;
      break;
    case TYPE::L:
      m_dirs = {true, false, true, false};
      m_type = type;
      break;
    case TYPE::F:
      m_dirs = {true, true, true, false};
      m_type = type;
      break;
    default:
      throw runtime_error("Wrong parameter in MazeCard::set()");
      break;
  }

  // Set rotation to zero degrees
  m_rotation = 0;
}

bool MazeCard::canGo(MazeCard::CANGO dir)
{
  bool retVal = false;

  switch (dir) {
    case CANGO::LEFT:
      retVal = m_dirs[0];
      break;
    case CANGO::UP:
      retVal = m_dirs[1];
      break;
    case CANGO::RIGHT:
      retVal = m_dirs[2];
      break;
    case CANGO::DOWN:
      retVal = m_dirs[3];
      break;
    default:
      throw runtime_error("Wrong parameter in MazeCard::cango()");
      break;
  }

  return retVal;
}

void MazeCard::turnRight()
{
  // Rotate vector of directories
  rotate(m_dirs.begin(), m_dirs.begin()+3, m_dirs.end());

  // Change value of rotation
  m_rotation = (m_rotation + 90) % 360;
}

MazeCard::TYPE MazeCard::type()
{
  return m_type;
}

int MazeCard::rotation()
{
  return m_rotation;
}

bool MazeCard::setTreasure(TreasureCard *treasureCard)
{
  if (m_treasureCard == nullptr) {
    m_treasureCard = treasureCard;
    return true;
  }
  else {
    return false;
  }
}

void MazeCard::clearTreasure()
{
  m_treasureCard = nullptr;
}

TreasureCard *MazeCard::getTreasureCard() const
{
    return m_treasureCard;
}

void MazeCard::setTreasureCard(TreasureCard *treasureCard)
{
    m_treasureCard = treasureCard;
}


TreasureCard *MazeCard::getTreasure()
{
    return m_treasureCard;
}

void MazeCard::setPlayer(Player *player)
{
    m_player = player;
}

Player *MazeCard::getPlayer()
{
    return m_player;
}

bool MazeCard::operator==(const MazeCard &rhs) const
{
  return m_dirs == rhs.m_dirs;
}

bool MazeCard::operator!=(const MazeCard &rhs) const
{
  return !(*this == rhs);
}
