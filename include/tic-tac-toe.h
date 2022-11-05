#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdbool.h>

#define X 'X'
#define O 'O'
#define T 'T'

struct Move
{
    int row;
    int column;
};

bool canMakeMove(char board[3][3], struct Move move);
bool makeMove(char board[3][3], struct Move move, char moveSymbol);
void copyBoard(char originalBoard[3][3], char duplicateBoard[3][3]);
int minimax(char board[3][3], int depth, bool isMaximizing);
char generatePlayerChar(int player);
char checkWinner(char board[3][3]);
bool hasAvailableSpot(char board[3][3]);

#endif