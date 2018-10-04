#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "randomizer.h"
#include "gameboard.h"

void Randomizer::Initialize()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }
}

Direction Randomizer::Orientation()
{
    Initialize();
    return (Direction)(rand() % 2);
}

int Randomizer::Position(int length)
{
    Initialize();
    return rand() % (GameBoard::GridSize - length);
}