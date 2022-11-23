#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdbool.h>

#define X 'X'
#define O 'O'
#define T 'T'

typedef struct Move
{
    int row;
    int column;
} Move;

typedef enum DifficultyMode
{
    Easy,
    Medium,
    Impossible,
} DifficultyMode;

bool canMakeMove(char board[3][3], Move move);
bool makeMove(char board[3][3], Move move, char moveSymbol);
void copyBoard(char originalBoard[3][3], char duplicateBoard[3][3]);

char generatePlayerChar(int player);
char checkWinner(char board[3][3]);
bool hasAvailableSpot(char board[3][3]);

Move getBestMove(char board[3][3], DifficultyMode mode);
int minimax(char board[3][3], bool isMaximizing, int depth, int alpha, int beta, DifficultyMode mode);


#endif