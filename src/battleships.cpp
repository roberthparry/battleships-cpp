#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "gameboard.h"
#include "firingresult.h"

int main()
{
    GameBoard board;
    board.Setup();
    do
    {
        char cellReference[255];

        board.Print();
        printf("Enter cell to fire at (e.g. A1, B1, ...) or q to quit: ");
        scanf("%s", cellReference);
        if (strlen(cellReference) == 1 && tolower(cellReference[0]) == 'q')
        {
            printf("Bye!\n");
            return 0;
        }

        int row, column;
        if (!GameBoard::TranslateCellReference(cellReference, row, column))
        {
            printf("'%s' is not a valid cell.\n", cellReference);
            continue;
        }

        FiringResult result = board.FireMissile(row, column);
        switch (result)
        {
        case FiringResult_Hit:
            printf("Hit!\n");
            break;
        case FiringResult_Missed:
            printf("Missed!\n");
            break;
        default:
            printf("You've already been there!\n");
            break;
        }

    } while (!board.IsGameWon());

    board.Print();
    printf("Congratulations, you Won!\n");
}