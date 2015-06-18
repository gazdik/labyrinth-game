/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file Player.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "Player.h"

Player::Player(int num)
  :m_number {num} , m_score {0}
{
}

void Player::incrementScore()
{
  m_score++;
}

void Player::setTreasure(TreasureCard *treasure)
{
  m_treasure = treasure;
}

TreasureCard *Player::getTreasure()
{
  return m_treasure;
}

int Player::score()
{
  return m_score;
}

int Player::number()
{
  return m_number;
}
