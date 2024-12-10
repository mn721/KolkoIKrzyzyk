#include <iostream>
#include "Board.h"
#include "Player.h"
#include "GameManager.h" 

int main(){ srand(time(0)); GameManager Manager; Manager.gameLoop(true); return 0; }