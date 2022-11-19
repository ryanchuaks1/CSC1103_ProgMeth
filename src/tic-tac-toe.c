#include "../include/tic-tac-toe.h"
#include "../include/helpers.h"

char generatePlayerChar(int player)
{
    return ((player == 1) ? 'X' : 'O');
}

/// @brief Given a board, check if there's any available spot available to use
/// @param board
/// @return
bool hasAvailableSpot(char board[3][3])
{
    int count = 0;
    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols < 3; cols++)
        {
            Move attemptedMove = {rows, cols};
            if (canMakeMove(board, attemptedMove))
                count++;
        }
    }

    if (count > 0)
        return true;
    return false;
}

/// @brief Check for both vertical/horizontal/diagonal winner
/// @param board
/// @return Return 'X'/'O'/'T'/-1 depending on who won the game/tie
char checkWinner(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        // Check horizontal winning condition
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        {
            return board[i][0];
        }

        // Check vertical winning condition
        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            return board[0][i];
        }
    }
    // Check for diagonal winning condition
    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
    {
        return board[0][0];
    }
    else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
    {
        return board[0][2];
    }

    // There's no winner so we check if there's any empty space left yet.
    if (!hasAvailableSpot(board))
        return 'T';
    return -1;
}

/// @brief Place the character on the board
/// @param board
/// @param move
/// @param moveSymbol
/// @return Return true depending on whether it successfully modified the board
bool makeMove(char board[3][3], Move move, char moveSymbol)
{
    if (canMakeMove(board, move))
    {
        board[move.row][move.column] = moveSymbol;
        return true;
    }
    return false;
}

/// @brief Takes in a board and does out of bound checking as well as check on available spots on the board
/// @param board The board to check
/// @param move A single structure consisting of row,column
/// @return A boolean true/false whether you can place a move on a specific area on the board
bool canMakeMove(char board[3][3], Move move)
{
    if ((move.row > 3) || (move.column > 3))
        return false;
    if ((board[move.row][move.column] != X) && (board[move.row][move.column] != O))
        return true;
    return false;
}

/// @brief Calls each available spot on the board and determine using minimax which is the next bestMove supposed to be
/// @param board Given a board, what's the best next move to do next
/// @return A structure which contains the best determined move to do next
Move getBestMove(char board[3][3], DifficultyMode mode)
{
    int bestScore = -1000;
    Move bestMove;
    int alpha = -10000;
    int beta = 10000;

    if (mode == Easy)
    {
    }

    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols < 3; cols++)
        {
            Move attemptedMove = {rows, cols};
            if (canMakeMove(board, attemptedMove))
            {
                char duplicatedBoard[3][3];
                copyBoard(board, duplicatedBoard);

                // Attempt to put in the next possible move.
                makeMove(duplicatedBoard, attemptedMove, X);
                int tempScore = 0;

                if (mode == Medium)
                {
                    tempScore = minimax(duplicatedBoard, 0, alpha, beta, false, Medium);
                }
                else if (mode == Impossible)
                {
                    tempScore = minimax(duplicatedBoard, 0, alpha, beta, false, Impossible);
                }

                if (tempScore > bestScore)
                {
                    bestScore = tempScore;
                    bestMove = attemptedMove;
                }
            }
        }
    }
    return bestMove;
}

// TODO: Include alpha beta pruning
/// @brief The code looks 90% similar to getBestMove. However, one thing that differentiates them is it goes recursively into every single board for possibility.
/// @param board
/// @param depth How deep has the recursion gone
/// @param isMaximizing Checks which player turn. AI is usually maximizing. Player is usually minimizing.
/// @return The
int minimax(char board[3][3], int depth, int alpha, int beta, bool isMaximizing, DifficultyMode mode)
{
    // Remember that if we do not calculate how to get the results somewhere in this function,
    // Return bestScore would be unable to run as there is no one returning a value.
    char winResult = checkWinner(board);
    switch (winResult)
    {
    case X:
        return (10 - depth);
    case O:
        return (-10 + depth);
    case T:
        return 0;
    }

    if (isMaximizing)
    {
        int bestScore = -1000;
        for (int rows = 0; rows < 3; rows++)
        {
            for (int cols = 0; cols < 3; cols++)
            {
                Move attemptedMove = {rows, cols};
                if (canMakeMove(board, attemptedMove)) // Check for available spot in the board.
                {
                    char duplicateBoard[3][3];
                    copyBoard(board, duplicateBoard);

                    makeMove(duplicateBoard, attemptedMove, X);
                    // As long as the game doesn't end recursively call it till we get an end state.
                    int score = minimax(duplicateBoard, depth++, alpha, beta, false, mode);
                    int bestScore = max(bestScore, score);

                    // Medium Mode will do alpha beta pruning
                    if (mode == Medium)
                    {
                        if (beta <= alpha)
                        {
                            break;
                        }
                    }
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int rows = 0; rows < 3; rows++)
        {
            for (int cols = 0; cols < 3; cols++)
            {
                Move attemptedMove = {rows, cols};
                if (canMakeMove(board, attemptedMove))
                {
                    char duplicateBoard[3][3];
                    copyBoard(board, duplicateBoard);

                    makeMove(duplicateBoard, attemptedMove, O);
                    // As long as the game doesn't end recursively call it till we get an end state.
                    int score = minimax(duplicateBoard, depth++, alpha, beta, true, mode);
                    int bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

/// @brief Duplicates a board from originalBoard to duplicateBoard which creates a exact value but different array pointer
/// @param originalBoard
/// @param duplicateBoard
void copyBoard(char originalBoard[3][3], char duplicateBoard[3][3])
{
    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols < 3; cols++)
        {
            duplicateBoard[rows][cols] = originalBoard[rows][cols];
        }
    }
}