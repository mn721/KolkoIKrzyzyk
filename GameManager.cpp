#include "GameManager.h"
#include "windows.h"

void GameManager::setGame(Player*& p1, Player*& p2, Board*& board)
{
	std::cout << "Wybierz typ Gracza1 (Krzyzyk):\n1.Czlowiek\n2.Komputer\n";
	
	int choice = 0;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		p1 = new PlayerHuman;
		break;
	case 2:
		p1 = new PlayerComputer;
		break;
	default:
		std::cout << "		Note: wybrano niepoprawna opcje. Domyslnie ustawiam typ gracza na: Komputer\n\n";
		p1 = new PlayerComputer;
		break;
	}

	std::cout << "\nWybierz typ Gracza2 (Kolko):\n1.Czlowiek\n2.Komputer\n";

	choice = 0;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		p2 = new PlayerHuman;
		break;
	case 2:
		p2 = new PlayerComputer;
		break;
	default:
		std::cout << "		Note: wybrano niepoprawna opcje. Domyslnie ustawiam typ gracza na: Komputer\n";
		p2 = new PlayerComputer;
		break;
	}
	
	std::cout << "\nWybierz rozmiar planszy (musi to byc liczba calkowita nie mniejsza od 3 i nie wieksza od 50)\n";

	choice = 0;
	std::cin >> choice;
	GameBoardPtr = new Board(choice);
	if (choice < 3 || choice >= 50 )
		std::cout << "		Note: wybrano niepoprawna opcje. Domyslnie ustawiam rozmiar planszy na: 3x3\n";

	Player1Ptr = p1;
	Player2Ptr = p2;
}

void GameManager::gameLoop(bool newGame)
{
	Player* g1;
	Player* g2;
	Board* GameBoard;

	if (newGame)
		this->setGame(g1, g2, GameBoard);

	bool winnerKrzyzyk = false;
	bool winnerKolko = false;

	GameBoardPtr->printChart();
	while (!GameBoardPtr->tie() && !winnerKolko)
	{
		Player1Ptr->makeMove(*GameBoardPtr, States::krzyzyk) ? winnerKrzyzyk : winnerKrzyzyk = true;

		if (GameBoardPtr->tie() || winnerKrzyzyk)
			break;

		Player2Ptr->makeMove(*GameBoardPtr, States::kolko)   ? winnerKolko : winnerKolko = true;
	}

	if (winnerKrzyzyk)
	{
		SetConsoleTextAttribute(GameBoardPtr->getHConsole(), 4);
		std::cout << "Gra zakonczona wygrana Gracza1 (Krzyzyk). Oto finalny wyglad planszy:\n\n";
	}
	else if (winnerKolko)
	{
		SetConsoleTextAttribute(GameBoardPtr->getHConsole(), 9);
		std::cout << "Gra zakonczona wygrana Gracza2 (Kolko).   Oto finalny wyglad planszy:\n\n";
	}
	else
	{
		SetConsoleTextAttribute(GameBoardPtr->getHConsole(), 14);
		std::cout << "Gra zakonczona remisem. Oto finalny wyglad planszy : \n\n";
	}
	
	SetConsoleTextAttribute(GameBoardPtr->getHConsole(), 15);
	GameBoardPtr->printChart();
	std::cout << "Czy chcesz zagrac jeszcze raz?\n1. Tak, z tymi samymi ustawieniami.\n2. Tak, z innymi ustawieniami.\n3. Nie, koncze na dzisiaj\n";

	int decision = 3;
	std::cin >> decision;
	switch (decision)
	{
	case 1:
		GameBoardPtr->resetChart();
		gameLoop(false);
		break;
	case 2:
		gameLoop(true);
		break;
	case 3:
		std::cout << "\n\n\nMilego dnia / wieczoru!\n\n";
		exit(0);
		break;
	default:
		std::cout << "\n\n\nMilego dnia / wieczoru!\n\n";
		exit(0);
		break;
	}
}