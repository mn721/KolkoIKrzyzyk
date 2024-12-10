#include "Player.h"

#pragma once
class GameManager
{
public:
	Player* Player1Ptr;
	Player* Player2Ptr;
	Board* GameBoardPtr;

	void gameLoop(bool);
	void setGame(Player*&, Player*&, Board*&);
};

