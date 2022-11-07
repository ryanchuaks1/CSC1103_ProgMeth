#include "../include/tic-tac-toe.h"
#include "../include/helpers.h"
#include "../include/screens.h"

#include <stdio.h>

#define gridSize 150
#define gridThickness 10

////// Global Variables ////////
enum GameplayMode gameMode;
char board[3][3] = {
    {'0', '1', '2'},
    {'3', '4', '5'},
    {'6', '7', '8'},
};
RenderTexture2D screenTexture;
RenderTexture2D XTextures;
RenderTexture2D OTextures;
///////////////////////////////

////// Functions Prototype ////////
static void CreateCrossTexture(RenderTexture2D texture);
static void CreateCircleTexture(RenderTexture2D texture);


void InitGameplayScreen(enum GameplayMode selectedMode)
{
    gameMode = selectedMode;

    screenTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    XTextures = LoadRenderTexture(gridSize, gridSize);
    OTextures = LoadRenderTexture(gridSize, gridSize);

    CreateCrossTexture(XTextures);
    CreateCircleTexture(OTextures);
}

static void CreateCrossTexture(RenderTexture2D texture)
{
    BeginTextureMode(texture);
    ClearBackground(WHITE);
	DrawRectanglePro((Rectangle){35, 13, gridSize - 5, 25}, (Vector2){0, 0}, 45.0f, RED);
	DrawRectanglePro((Rectangle){135, 30, gridSize - 5, 25}, (Vector2){0, 0}, 135.0f, RED);
    EndTextureMode();
}

static void CreateCircleTexture(RenderTexture2D texture)
{
    BeginTextureMode(texture);
    ClearBackground(WHITE);
    DrawCircle(gridSize / 2, gridSize / 2, gridSize / 2 - 5, BLUE); // Outer circle
	DrawCircle(gridSize / 2, gridSize / 2, 45, WHITE);		
    EndTextureMode();
}

/// @brief Return a Move structure upon hovering on the board.
static struct Move checkCollisionWithBoard()
{
    struct Move getHoveredMove;
    Vector2 gridVectors = {155, 155};
    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols < 3; cols++)
        {
            // Check if the dimension has collided with the box
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){rows * (gridSize + gridThickness) + gridVectors.x, cols * (gridSize + gridThickness) + gridVectors.y, gridSize, gridSize}))
            {
                getHoveredMove.row = rows;
                getHoveredMove.column = cols;
            }
            else
            {
                getHoveredMove.row = -1;
                getHoveredMove.column = -1;
            }
        }
    }
    return getHoveredMove;
}


void UpdateGameplayScreen()
{
    struct Move uselessMove = checkCollisionWithBoard();
    if (canMakeMove(board, uselessMove))
    {
        printf("Can make move on [%d][%d]\n", uselessMove.column, uselessMove.row);
    }

    // It's within while loop so the bottom part probably doesn't work
    int playerTurn = 0;
    if (gameMode == Multiplayer)
    {
        char playerChar = generatePlayerChar(playerTurn);
        // Some function to get mouse hovered and get the moveHovered
        struct Move mouseHoveredMove;
        if (canMakeMove(board, mouseHoveredMove) && IsMouseButtonPressed(0))
        {
            makeMove(board, mouseHoveredMove, playerChar);
            playerTurn = !playerTurn;
        }
    }
    else if (gameMode == MediumAI)
    {
        // Wait for Sean
    }
    else if (gameMode == ImpossibleAIMode)
    {
        // First step always belong to the user
        if (playerTurn == 0)
        {
            char playerChar = generatePlayerChar(playerTurn);
            // Some function to get mouse hovered and get the moveHovered
            struct Move mouseHoveredMove;
            if (canMakeMove(board, mouseHoveredMove) && IsMouseButtonPressed(0))
            {
                makeMove(board, mouseHoveredMove, playerChar);
                playerTurn = !playerTurn;
            }
        }
        else
        {
            char playerChar = generatePlayerChar(playerTurn);
            struct Move bestMove = getBestMove(board);
            // By right we don't need this because internally canMakeMove already has the check
            if (canMakeMove(board, bestMove))
            {
                makeMove(board, bestMove, playerChar);
            }
        }
    }
    // Winner check below
}

void DrawGameplayScreen()
{
    BeginDrawing();
    BeginTextureMode(screenTexture);

    ClearBackground(WHITE);

    // Draw a big square which is the background for the board
    DrawRectangle(145, 145, (gridSize * 3 + gridThickness * 2) + 20, (gridSize * 3 + gridThickness * 2) + 20, BLACK);
    // Draw empty boxes on the grid
    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols <3; cols++)
        {
            // Check and print in values that are already occupied by X and O and draw textures out.
            if (board[rows][cols] == 'X' || board[rows][cols] == 'O')
            {
                //Draw the texture and slot it into the slot
                DrawTextureRec((board[rows][cols] == 'X') ? XTextures.texture : OTextures.texture, (Rectangle){0, 0, gridSize, -gridSize}, (Vector2){rows * (gridSize + gridThickness) + 155, cols * (gridSize + gridThickness) + 155}, WHITE);
            }
            else
            {
                //TODO: Add hover events
				// if (CheckCollisionPointRec((Vector2){GetMouseX(), GetMouseY()}, (Rectangle){i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize}))
				// {
				// 	DrawRectangle(i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize, LIGHTGRAY);
				// }
                DrawRectangle(rows * (gridSize + gridThickness) + 155, cols * (gridSize + gridThickness) + 155, gridSize, gridSize, WHITE);
            }
        }
    }
    if (checkWinner(board) == T)
    {
        DrawText("Draw", 145, 675, 75, BLACK);
    }
    else if (checkWinner(board) == X)
    {
        DrawText("Player X wins!", 145, 675, 75, BLACK);
    }
    else if (checkWinner(board) == O)
    {
        DrawText("Player O wins!", 145, 675, 75, BLACK);
    }

    EndTextureMode();
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, 800, -800}, (Vector2){0, 0}, WHITE);
    EndDrawing();
}


void UnloadGameplayScreen()
{ 
}

int FinishGameplayScreen()
{

}
