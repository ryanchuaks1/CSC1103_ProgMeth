#include <stdio.h>

enum GameMode
{
    Multiplayer,
    Bots
};

void MultiplayerMode();
void BotsMode(int difficultyMode);

int CheckWinConditions(char *board);
void GenerateBoard(char *board);
void GenerateSquare();
int CanMakeMove(int position, char *board);
void MakeMove(char symbol, int position, char *board);

int main(void)
{
    int gameSelection;

    do
    {
        printf("Select game mode \n");
        printf("1 = Multiplayer \n");
        printf("2 = Bots \n");
        scanf("%d", &gameSelection);
    } while ((gameSelection != 1) && (gameSelection != 2));

    switch (gameSelection)
    {
    case 1:
        MultiplayerMode();
        break;

    case 2:
        break;

    default:
        break;
    }

    return 0;
}

void MultiplayerMode()
{
    int inGame = 1;
    // Define which player turn is it.
    int player = 0;

    char board[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    while (inGame == 1)
    {
        char marksSymbol = (player) ? 'X' : 'O';
        int boardSelection;
        printf("Player %c turn. Please enter a number that is shown in the board below. \n", marksSymbol);
        GenerateBoard(board);
        scanf("%d", &boardSelection);

        while (!CanMakeMove(boardSelection, board))
        {
            printf("The selected board position has already been chosen. \n");
            printf("Please enter a blank position \n");
            scanf("%d", &boardSelection);
        }
        MakeMove(marksSymbol, boardSelection, board);
        int result = CheckWinConditions(board);
        if (result == 1)
        {
            printf("The winner is %c \n", marksSymbol);
            inGame = 0;
        }
        else if (result == 2)
        {
            printf("There is no winner \n");
            inGame = 0;
        }
        player = !player;
    }
}

void BotsMode(int difficultyMode)
{
}

void GenerateBoard(char *board)
{
    printf("|---------------------------|\n");
    printf("|        |          |       |\n");
    printf("|   %c    |    %c     |   %c   |\n", board[0], board[1], board[2]);
    printf("|---------------------------|\n");
    printf("|   %c    |    %c     |   %c   |\n", board[3], board[4], board[5]);
    printf("|---------------------------|\n");
    printf("|   %c    |    %c     |   %c   |\n", board[6], board[7], board[8]);
    printf("|        |          |       |\n");
    printf("|---------------------------|\n");
}

//TODO: Validation for out of bound board
int CanMakeMove(int position, char *board)
{
    if (board[position] != 'X' && board[position] != 'O')
    {
        return 1;
    }
    return 0;
}

void MakeMove(char symbol, int position, char *board)
{
    board[position] = symbol;
}

//  TODO: Tie logic
//  Results will return 3 types.
//  0 = Game has not ended (Continue the loop)
//  1 = Game has ended with a winner
//  2 = Game has tied
int CheckWinConditions(char *board)
{
    if (((board[0] == board[3]) && (board[3] == board[6])) || ((board[1] == board[4]) && (board[4] == board[7])) || ((board[2] == board[5]) && (board[5] == board[8])))
    {
        return 1;
    }

    else if (((board[0] == board[1]) && (board[1] == board[2])) || ((board[3] == board[4]) && (board[4] == board[5])) || ((board[6] == board[7]) && (board[7] == board[8])))
    {
        return 1;
    }
    else if (((board[0] == board[4]) && (board[4] == board[8])) || ((board[2] == board[4]) && (board[4] == board[6])))
    {
        return 1;
    }
    else
    {
        int count = 0;
        for (int i = 0; i < sizeof(board); i++)
        {
            if (board[i] == 'X' || board[i] == 'O')
            {
                count++;
            }
        }
        if (count == sizeof(board))
        {
            return 2;
        }
        return 0;
    }
}