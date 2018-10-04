#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "gameboard.h"
#include "randomizer.h"
#include "direction.h"
#include "cellstatus.h"
#include "cell.h"

void GameBoard::Setup()
{
    PlaceShip(&_battleShip);
    PlaceShip(&_destroyer1);
    PlaceShip(&_destroyer2);
}

void GameBoard::PlaceShip(Ship *ship)
{
    Direction direction;
    int position1;
    int position2;

    do
    {
        direction = Randomizer::Orientation();
        position1 = Randomizer::Position(ship->GetLength());
        position2 = Randomizer::Position(1);
    } while (!CanPlaceShip(ship, position1, position2, direction));

    DoPlaceShip(ship, position1, position2, direction);
}

void GameBoard::DoPlaceShip(Ship *ship, int position1, int position2, Direction direction)
{
    if (direction == Direction_Down)
    {
        for (int i = 0; i < ship->GetLength(); i++)
        {
            _cellGrid[position1 + i][position2].OccupyingShip = ship;
        }
    }
    else
    {
        for (int i = 0; i < ship->GetLength(); i++)
        {
            _cellGrid[position2][position1 + i].OccupyingShip = ship;
        }
    }
}

bool GameBoard::CanPlaceShip(Ship *ship, int position1, int position2, Direction direction)
{
    if (direction == Direction_Down)
    {
        for (int i = 0; i < ship->GetLength(); i++)
        {
            if (_cellGrid[position1 + i][position2].OccupyingShip != NULL)
                return false;
        }
    }
    else
    {
        for (int i = 0; i < ship->GetLength(); i++)
        {
            if (_cellGrid[position2][position1 + i].OccupyingShip != NULL)
                return false;
        }
    }
    return true;
}

void GameBoard::Print()
{
    printf("     ╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n");
    printf("     ║ A │ B │ C │ D │ E │ F │ G │ H │ I │ J ║\n");
    printf("╔════╬═══╪═══╪═══╪═══╪═══╪═══╪═══╪═══╪═══╪═══╣\n");

    for (int row = 0; row < GridSize; row++)
        PrintRow(row);
}

void GameBoard::PrintRow(int row)
{
    if (row == GridSize - 1)
        printf("║ %d ║", row + 1);
    else
        printf("║  %d ║", row + 1);

    for (int column = 0; column < GridSize; column++)
    {
        printf(" %c ", (char)SymbolForCell(_cellGrid[row][column]));
        if (column == GridSize - 1)
            printf("║\n");
        else
            printf("│");
    }
    if (row == GridSize - 1)
        printf("╚════╩═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n");
    else
        printf("╟────╫───┼───┼───┼───┼───┼───┼───┼───┼───┼───╢\n");
}

char GameBoard::SymbolForCell(const Cell &cell)
{
    if (cell.Status != CellStatus_Shelled)
        return ' ';

    return (cell.OccupyingShip == NULL) ? 'x' : '#';
}

bool GameBoard::TranslateCellReference(const char *cellReference, int &row, int &column)
{
    static char columns[] = "abcdefghij";

    if (cellReference == NULL || *cellReference == '\0')
        return false;

    char* occurrence = strchr(columns, tolower(cellReference[0]));
    if (occurrence == NULL)
        return false;

    column = occurrence - columns;

    row = atoi(cellReference+1);
    if (row < 1 || row > GridSize)
        return false;

    row--;
    return true;
}

bool GameBoard::IsGameWon()
{
    return _destroyer1.IsDestroyed() && _destroyer2.IsDestroyed() && _battleShip.IsDestroyed();
}

FiringResult GameBoard::FireMissile(int row, int column)
{
    Cell &cell = _cellGrid[row][column];

    if (cell.Status == CellStatus_Shelled)
        return FiringResult_Repeat;

    cell.Status = CellStatus_Shelled;

    if (cell.OccupyingShip == NULL)
        return FiringResult_Missed;

    cell.OccupyingShip->TakeHit();
    return FiringResult_Hit;
}