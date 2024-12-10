#include "Board.h"

Board::Board(int size)
{
    m_Size = (size >= 3 && size <= 50) ? size : 3;
    m_Tab = new States * [m_Size];

    for (int i = 0; i < m_Size; i++)
        m_Tab[i] = new States[m_Size];

    resetChart(); // bo i tak przypisuje puste wartosci
}

Board::Board(const Board& other)
{
    m_Size = other.m_Size;

    m_Tab = new States * [m_Size];
    for (int i = 0; i < m_Size; i++)
    {
        m_Tab[i] = new States[m_Size];
    }

    for (int i = 0; i < m_Size; i++)
    {
        for (int j = 0; j < m_Size; j++)
        {
            m_Tab[i][j] = other.m_Tab[i][j];
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < m_Size; i++)
        delete[] m_Tab[i];
    delete[] m_Tab;
}

void Board::printChart()
{
    std::string sep;

    std::cout << "\n   ";
    for (int i = 0; i < m_Size; i++)
    {
        i >= 9 ? sep = " " : sep = "  ";
        std::cout << i + 1 << sep;
    }
    std::cout << std::endl;

    for (int i = 0; i < m_Size; i++)
    {
        i >= 9 ? sep = " " : sep = "  ";
        std::cout << i + 1 << sep;
        for (int j = 0; j < m_Size; j++)
        {
            switch (m_Tab[i][j])
            {
            case puste:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            case krzyzyk:
                SetConsoleTextAttribute(hConsole, 4);
                break;
            case kolko:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            }

            std::cout << m_Symbols[m_Tab[i][j]] << "  ";
            SetConsoleTextAttribute(hConsole, 15);
        }
           
        std::cout << std::endl;
    }
    std::cout << "\n";
}

void Board::resetChart()
{
    for (int i = 0; i < m_Size; i++)
        for (int j = 0; j < m_Size; j++)
            m_Tab[i][j] = puste;
}

bool Board::checkField(int x, int y)
{
    if (x >= 0 && x < m_Size && y >= 0 && y < m_Size)
        return m_Tab[y][x] == puste;
    return false; 
}

bool Board::setField(int x, int y, States playerSymbol)
{
    if (checkField(x, y))
    {
        m_Tab[y][x] = playerSymbol;
        return true;
    }
    return false;
}

bool Board::tie()
{
    for (int i = 0; i < m_Size; i++)
        for (int j = 0; j < m_Size; j++)
            if (m_Tab[i][j] == puste)      
                return false;
    return true;
}