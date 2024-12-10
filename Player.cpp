#include "Player.h"
#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include <windows.h>

bool PlayerHuman::makeMove(Board& board, States playerSymbol)
{
    int x, y;
    
    std::cout << "Tura gracza z symbolem: " << board.getSymbols()[playerSymbol] << std::endl;
    std::cout << "      Podaj wspolrzedna x (nr kolumny): ";
    std::cin >> x;
    std::cout << "      Podaj wspolrzedna y (nr wiersza): ";
    std::cin >> y;

    while (!board.setField(x - 1, y - 1, playerSymbol))
    {
        std::cout << "Nieprawidlowy ruch! Sproboj ponownie." << std::endl;
        std::cout << "      Note: minimalna wartosc: 1, masymalna wartosc: " << board.getSize() << std::endl;
        std::cout << "      Podaj wspolrzedna x (nr kolumny): ";
        std::cin >> x;
        std::cout << "      Podaj wspolrzedna y (nr wiersza): ";
        std::cin >> y;
    }
    
    board.printChart();

    return !this->checkWinner(board, x - 1, y - 1, playerSymbol);
}

bool PlayerComputer::makeMove(Board& board, States playerSymbol)
{
    int x, y;

    std::cout << "Tura gracza z symbolem: " << board.getSymbols()[playerSymbol] << std::endl;
    do
    {
        x = rand() % board.getSize();
        y = rand() % board.getSize();
    } while (!board.setField(x, y, playerSymbol));
    Sleep(1000);
    std::cout << "      Komputer (" << board.getSymbols()[playerSymbol] << ") wykonal ruch na (" << x + 1 << ", " << y + 1 << ").\n";

    board.printChart();

    return !this->checkWinner(board, x, y, playerSymbol);
}

bool Player::checkWinner(Board& board, int y, int x, States symbol)
{
    int size = board.getSize();
    int counterColumns = 0;
    int counterRows = 0;
    int counterDiagonal1 = 0;
    int counterDiagonal2 = 0;

    int iterator = board.getSize() - 1;
    for (int i = 0; i < board.getSize(); i++)
    {
        // pion
        if (board.getTab()[i][y] == symbol)
            counterColumns++;
        // poziom
        if (board.getTab()[x][i] == symbol)
            counterRows++;
        // przekatna od lewego gornego do prawego dolnego
        if (board.getTab()[i][i] == symbol)
            counterDiagonal1++;
        // przekatna od prawego gornego do lewego dolnego 
        if (board.getTab()[iterator--][i] == symbol)
            counterDiagonal2++;
    }

    return (counterColumns == size || counterRows == size || counterDiagonal1 == size || counterDiagonal2 == size);
}