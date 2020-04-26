#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    NOUGHTS,
    CROSSES,
    BORDER,
    EMPTY
};

enum
{
    PLAYERWIN,
    COMPUTERWIN,
    DRAW
};

const int convertTo25[9] = {6, 7, 8, 11, 12, 13, 16, 17, 18};
const int directions[4] = {1, 5, 4, 6};

void initializeBoard(int *board)
{
    int i;
    for (i = 0; i < 25; i++)
    {
        board[i] = BORDER;
    }
    for (i = 0; i < 9; i++)
    {
        board[convertTo25[i]] = EMPTY;
    }
}

void printBoard(const int *board)
{
    char pieces[] = "OX|-";

    printf("\nBoard:\n");
    for (int i = 0; i < 9; i++)
    {
        if (i != 0 && i % 3 == 0)
        {
            printf("\n");
        }
        printf("%4c", pieces[board[convertTo25[i]]]);
    }
    printf("\n\n");
}

int hasEmptySquare(const int *board)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[convertTo25[i]] == EMPTY)
            return 1;
    }
    return 0;
}

int getPlayerMove(const int *board)
{
    char playerInput[4];

    int validMove = 0;
    int move = -1;

    while (validMove == 0)
    {
        printf("Type a number between 1 to 9: ");
        fgets(playerInput, 3, stdin);
        fflush(stdin);

        if (strlen(playerInput) != 2)
        {
            printf("Invalid input length\n");
            continue;
        }
        if (sscanf(playerInput, "%d", &move) != 1)
        {
            move = -1;
            printf("Invalid character\n");
            continue;
        }
        if (move < 1 || move > 9)
        {
            move = -1;
            printf("Invalid number\n");
            continue;
        }
        move--;
        if (board[convertTo25[move]] != EMPTY)
        {
            move = -1;
            printf("Square already occupied!\n");
            continue;
        }
        validMove = 1;
    }
    printf("Moving...");
    return convertTo25[move];
}

int getRandomComputerMove(const int *board)
{
    int availableMoves[9];
    int numberOfFreeSquares;
    for (int i = 0; i < 9; i++)
    {
        if (board[convertTo25[i]] == EMPTY)
        {
            availableMoves[numberOfFreeSquares++] = convertTo25[i];
        }
    }
    int randMove = (rand() % numberOfFreeSquares);
    return availableMoves[randMove];
}

int getComputerMove(const int *board) {}

void makeMove(int *board, const int square, const side)
{
    board[square] = side;
}

int getNumberForDirection(int startSquare, const int direction, const int *board, const int side)
{
    int found = 0;
    while (board[startSquare] != BORDER)
    {
        if (board[startSquare] != side)
        {
            break;
        }
        found++;
        startSquare += direction;
    }
    return found;
}

int findThree(const int *board, const int sideIndex, const int side)
{
    int dir = 0;
    int counter = 1;

    for (int dirIndex = 0; dirIndex < 4; dirIndex++)
    {
        dir = directions[dirIndex];
        counter += getNumberForDirection(sideIndex + dir, dir, board, side);
        counter += getNumberForDirection(sideIndex + dir * -1, dir * -1, board, side);
        if (counter == 3)
        {
            break;
        }
        counter = 1;
    }
    return counter;
}

void runGame()
{
    int gameOver = 0;
    int side = CROSSES;
    int lastMoveMade = 0;
    int board[25];

    initializeBoard(&board[0]);
    printBoard(&board[0]);

    while (!gameOver)
    {
        if (side == CROSSES)
        {
            lastMoveMade = getPlayerMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = NOUGHTS;
        }
        else
        {
            lastMoveMade = getRandomComputerMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = CROSSES;
            printBoard(&board[0]);
        }
        if (findThree(board, lastMoveMade, side ^ 1) == 3)
        {
            printf("Game over!\n");
            if (side == NOUGHTS)
            {
                printf("Player wins");
            }
            else
            {
                printf("Computer winss");
            }
        }
        if (!hasEmptySquare(board))
        {
            gameOver = 1;
            printf("Game over!\nDRAW\n");
        }
    }
    printBoard(&board[0]);
}

int main()
{
    srand(time(NULL));
    runGame();
    return 0;
}
