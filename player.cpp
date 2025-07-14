#include "player.h"

Player::Player(QWidget * parent, const char * name, Configuration::State pCoin): QWidget(parent,name), config(new Configuration), playerCoin(pCoin)
{
}

Player::Player(const Player & otherPlayer):QWidget(dynamic_cast<QWidget *>(otherPlayer.parent()))
{
  delete config;
  config=new Configuration(*(otherPlayer.config));
  playerCoin=otherPlayer.playerCoin;
}

Player & Player::operator=(const Player & otherPlayer)
{
  config=new Configuration(*(otherPlayer.config));

  playerCoin=otherPlayer.playerCoin;
  return *this;
}
