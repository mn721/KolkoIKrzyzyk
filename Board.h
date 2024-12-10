#pragma once
#include <iostream>
#include <windows.h>

enum States
{
    kolko,
    krzyzyk,
    puste
};

class Board
{
public:
    Board(int size = 3);
    Board(const Board&); // na wszelki wypadek, jakby sie kiedys przydal
    ~Board();

    void printChart();
    void resetChart();
    bool checkField(int x, int y);
    virtual bool setField(int x, int y, States playerSymbol);

    int getSize() const { return m_Size; }
    States** getTab() const { return m_Tab; }
    const char* getSymbols() const { return m_Symbols;  }
    HANDLE getHConsole() const { return hConsole; }

    bool tie();

private:
    int m_Size;
    States** m_Tab;
    char m_Symbols[3] = { 'O', 'X', '_' };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
};