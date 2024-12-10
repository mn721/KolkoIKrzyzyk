#pragma once
#include "Board.h"

class Player
{
public:
    virtual ~Player() {}

    virtual bool makeMove(Board&, States) { return false; };
    bool checkWinner(Board&, int, int, States);
};

class PlayerHuman : public Player
{
public:
    ~PlayerHuman() override {}

    virtual bool makeMove(Board&, States) override;
};

class PlayerComputer : public Player
{
public:
    ~PlayerComputer() override {}

   virtual bool makeMove(Board&, States) override;
};