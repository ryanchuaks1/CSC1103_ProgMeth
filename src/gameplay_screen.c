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
int playerTurn = 0;
static Texture2D gameBackground;
RenderTexture2D screenTexture;
RenderTexture2D XTextures;
RenderTexture2D OTextures;
struct Move hoveredMove;
///////////////////////////////

////// Functions Prototype ////////
static void CreateCrossTexture(RenderTexture2D texture);
static void CreateCircleTexture(RenderTexture2D texture);
static struct Move getMoveOnHoveredBoard();

void InitGameplayScreen(enum GameplayMode selectedMode)
{
    gameMode = selectedMode;

    screenTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    gameBackground = LoadTexture("resources/game_background.png");
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

void UpdateGameplayScreen()
{
    hoveredMove = getMoveOnHoveredBoard();
    char playerSymbol = generatePlayerChar(playerTurn);
    if (gameMode == Multiplayer)
    {
        if (canMakeMove(board, hoveredMove) && IsMouseButtonPressed(0))
        {
            printf("%d\n", playerTurn);
            makeMove(board, hoveredMove, playerSymbol);
            playerTurn = !playerTurn;
        }
    }
    else if (gameMode == MediumAI)
    {
    }
    else if (gameMode == ImpossibleAI)
    {
        if (playerTurn == 0)
        {
            if (canMakeMove(board, hoveredMove) && IsMouseButtonPressed(0))
            {
                makeMove(board, hoveredMove, playerSymbol);
                playerTurn = !playerTurn;
            }
        }
        else
        {
            // AI Mode
            struct Move bestMove = getBestMove(board);
            printf("Best Move determined is [%d][%d]\n", bestMove.row, bestMove.column);
            makeMove(board, bestMove, playerSymbol);
            playerTurn = !playerTurn;
        }
    }

    // Variable that checks for texture so that the background can scroll
    textureScroll -= 0.5f;
    if (textureScroll <= -gameBackground.width * 2)
    {
        textureScroll = 0;
    }
}

struct Move getMoveOnHoveredBoard()
{
    // Sets a default out of bound error
    struct Move getHoveredMove = {-1, -1};
    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols < 3; cols++)
        {
            // Check whether mouse has collided with the grid.
            // Does some calculation to check whether it has hit the grid thickness too.
            Rectangle gridRectangle = {
                (rows * (gridSize + gridThickness) + 155),
                (cols * (gridSize + gridThickness) + 155),
                gridSize,
                gridSize};
            if (CheckCollisionPointRec(GetMousePosition(), gridRectangle))
            {
                getHoveredMove.row = rows;
                getHoveredMove.column = cols;
                return getHoveredMove;
            }
        }
    }
    return getHoveredMove;
}

void DrawGameplayScreen()
{
    BeginDrawing();
    BeginTextureMode(screenTexture);

    ClearBackground(WHITE);
    DrawTextureEx(gameBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(gameBackground, (Vector2){gameBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);
    // Draw a big square which is the background for the board
    DrawRectangle(145, 145, (gridSize * 3 + gridThickness * 2) + 20, (gridSize * 3 + gridThickness * 2) + 20, BLACK);
    // Draw empty boxes on the grid
    for (int rows = 0; rows < 3; rows++)
    {
        for (int cols = 0; cols < 3; cols++)
        {
            // Check and print in values that are already occupied by X and O and draw textures out.
            if (board[rows][cols] == X || board[rows][cols] == O)
            {
                // Draw the texture and slot it into the slot
                DrawTextureRec((board[rows][cols] == X) ? XTextures.texture : OTextures.texture, (Rectangle){0, 0, gridSize, -gridSize}, (Vector2){rows * (gridSize + gridThickness) + 155, cols * (gridSize + gridThickness) + 155}, WHITE);
            }
            else
            {
                DrawRectangle(rows * (gridSize + gridThickness) + 155, cols * (gridSize + gridThickness) + 155, gridSize, gridSize, (hoveredMove.column == cols && hoveredMove.row == rows) ? LIGHTGRAY: WHITE);
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
    UnloadRenderTexture(screenTexture);
    UnloadTexture(gameBackground);
    UnloadRenderTexture(XTextures);
    UnloadRenderTexture(OTextures);

}