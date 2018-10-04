#pragma once

#include <stdlib.h>

#include "cell.h"
#include "ship.h"
#include "firingresult.h"
#include "direction.h"

class GameBoard
{
  public:
    const static int GridSize = 10;

  private:
    Cell _cellGrid[GridSize][GridSize];
    Destroyer _destroyer1;
    Destroyer _destroyer2;
    BattleShip _battleShip;

  private:
    void PlaceShip(Ship *ship);
    void DoPlaceShip(Ship *ship, int position1, int position2, Direction direction);
    bool CanPlaceShip(Ship *ship, int position1, int position2, Direction direction);
    void PrintRow(int row);
    char SymbolForCell(const Cell &cell);

  public:
    ~GameBoard() {}
    GameBoard() {}
    void Setup();
    static bool TranslateCellReference(const char *cellReference, int &row, int &column);
    void Print();
    bool IsGameWon();
    FiringResult FireMissile(int row, int column);
};