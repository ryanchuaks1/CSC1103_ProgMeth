#include "../include/tic-tac-toe.h"
#include "../include/helpers.h"
#include "../include/screens.h"

#include <stdio.h>

#define gridSize 150
#define gridThickness 10

/** ----------------------------------------------------------------------------------------------------
 * Global Static Variables
 ---------------------------------------------------------------------------------------------------- */
// Static keeps the variables local to this file.
GameplayMode gameMode;
char static board[3][3] = {
    {'0', '1', '2'},
    {'3', '4', '5'},
    {'6', '7', '8'},
};
static int playerTurn = 0;
static int winner = -1;

static Texture2D gameBackground;
RenderTexture2D screenTexture;
RenderTexture2D XTextures;
RenderTexture2D OTextures;
Move hoveredMove;
static int homeHovered = -1;

/** ----------------------------------------------------------------------------------------------------
 * Local functions prototype
 ---------------------------------------------------------------------------------------------------- */
static void CreateCrossTexture(RenderTexture2D texture);
static void CreateCircleTexture(RenderTexture2D texture);
static Move getMoveOnHoveredBoard();
static void resetGrid(char board[3][3]);

/** ----------------------------------------------------------------------------------------------------
 * @brief Initiate the Gameplay Screen, runs only once when navigating to the screen
 * @param selectedMode contains which mode is selected by the player
 *
 * @date difficulty_screen.c last updated 20/11/2022
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void InitGameplayScreen(GameplayMode selectedMode)
{
    gameMode = selectedMode; // set the current gamemode

    screenTexture = LoadRenderTexture(800, 800);                   // Load texture for rendering (screen)
    gameBackground = LoadTexture("resources/game_background.png"); // Load background image
    XTextures = LoadRenderTexture(gridSize, gridSize);             // Load texture for rendering (X)
    OTextures = LoadRenderTexture(gridSize, gridSize);             // Load texture for rendering (O)

    playerTurn = 0;   // Sets the current player's turn to default (0 = player turn)
    homeHovered = -1; // Sets the default button hover to -1 which is nothing/default
    winner = -1;      // Sets the current winner to nobody/default
    resetGrid(board); // Resets the grid

    CreateCrossTexture(XTextures);  // Creates the texture for X
    CreateCircleTexture(OTextures); // Creates the texture for O
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Creates the X and O textures for the game
 * @param texture includes the declared texture variables for X and O
 ---------------------------------------------------------------------------------------------------- */
static void CreateCrossTexture(RenderTexture2D texture)
{
    BeginTextureMode(texture); // Begin drawing to render texture
    ClearBackground(WHITE);
    DrawRectanglePro((Rectangle){35, 13, gridSize - 5, 25}, (Vector2){0, 0}, 45.0f, RED);   // Diagonal cross
    DrawRectanglePro((Rectangle){135, 30, gridSize - 5, 25}, (Vector2){0, 0}, 135.0f, RED); // Diagonal cross
    EndTextureMode();                                                                       // Ends drawing to render texture
}

static void CreateCircleTexture(RenderTexture2D texture)
{
    BeginTextureMode(texture); // Begin drawing to render texture
    ClearBackground(WHITE);
    DrawCircle(gridSize / 2, gridSize / 2, gridSize / 2 - 5, BLUE); // Outer circle
    DrawCircle(gridSize / 2, gridSize / 2, 45, WHITE);              // inner circle
    EndTextureMode();                                               // Ends drawing to render texture
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Resets the X and O textures for the game
 * @param board the current game state
 ---------------------------------------------------------------------------------------------------- */
static void resetGrid(char board[3][3])
{
    board[0][0] = '0';
    board[0][1] = '1';
    board[0][2] = '2';
    board[1][0] = '3';
    board[1][1] = '4';
    board[1][2] = '5';
    board[2][0] = '6';
    board[2][1] = '7';
    board[2][2] = '8';
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Updates the gameplay screen parameters. This function runs about 60 times a second.
 * This loop is created from main.c in the UpdateDrawFrame() function
 * This function checks:
 *      If a grid is hovered using @param hoveredMove.
 *      If the user clicks on the grid
 *      If the user clicks on home button
 *      Current game state (win/lose)
 *      Ai move based on difficulty
 ---------------------------------------------------------------------------------------------------- */
void UpdateGameplayScreen()
{
    hoveredMove = getMoveOnHoveredBoard();              // Assign hovered move into hoveredMove
    char playerSymbol = generatePlayerChar(playerTurn); // Generate the player's turn character X or O
    winner = checkWinner(board);                        // Checks if there are any winners

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){25, 15, 115, 105})) // Check if Home button is hovered
    {
        homeHovered = 1;                                         // Return hovered status 1
        IsMouseButtonPressed(0) ? navigate(MainMenuScreen) : -1; // Navigate to main menu if home is clicked
    }
    else
    {
        homeHovered = -1; // return hovered status -1 (nothing/default)
    }

    if (winner == -1) // Game continue to run if there is no winner
    {
        if (gameMode == Multiplayer) // Check if its multiplayer mode
        {
            if (canMakeMove(board, hoveredMove) && IsMouseButtonPressed(0)) // Checks if user can make move and has clicked on grid
            {
                makeMove(board, hoveredMove, playerSymbol); // Make the move on board, hoveredmove, current player char
                playerTurn = !playerTurn;                   // Swaps the player's turns
            }
        }
        else if (gameMode == MediumAI) // Check if its Medium AI mode
        {
            if (playerTurn == 0) // Checks if its player turn
            {
                if (canMakeMove(board, hoveredMove) && IsMouseButtonPressed(0)) // Checks if user can make move and has clicked on grid
                {
                    makeMove(board, hoveredMove, playerSymbol); // Makes the move on board
                    playerTurn = !playerTurn;                   // Swaps the player's turns
                }
            }
            else // Checks if its AI turn
            {
                Move bestMove = getBestMove(board, Medium); // Makes the best move according to AI mode
                makeMove(board, bestMove, playerSymbol);    // Makes the move on the board
                playerTurn = !playerTurn;                   // Swaps the player's turns
            }
        }
        else if (gameMode == ImpossibleAI) // Check if its Impossible AI mode
        {
            if (playerTurn == 0) // Checks if its player turn
            {
                if (canMakeMove(board, hoveredMove) && IsMouseButtonPressed(0)) // Checks if user can make move and has clicked on grid
                {
                    makeMove(board, hoveredMove, playerSymbol); // Makes the move on board
                    playerTurn = !playerTurn;                   // Swaps the player's turns
                }
            }
            else
            {
                // AI Mode
                Move bestMove = getBestMove(board, Impossible); // Makes the best move according to AI mode
                makeMove(board, bestMove, playerSymbol);        // Makes the move on the board
                playerTurn = !playerTurn;                       // Swaps the player's turns
            }
        }
    }
    // Variable that checks for texture so that the background can scroll
    textureScroll -= 0.5f;
    if (textureScroll <= -gameBackground.width * 2)
    {
        textureScroll = 0;
    }
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Thic function checks which move is being hovered
 *
 * @return hoveredmove,
 ---------------------------------------------------------------------------------------------------- */
Move getMoveOnHoveredBoard()
{
    Move getHoveredMove = {-1, -1}; // Sets a default out of bound move
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

/** ----------------------------------------------------------------------------------------------------
 * @brief Updates the gameplay screen user interface. This function runs about 60 times a second.
 * This loop is created from main.c in the UpdateDrawFrame() function
 * This function renders the next frame of the program and renders it into the screen.
 ---------------------------------------------------------------------------------------------------- */
void DrawGameplayScreen()
{
    BeginDrawing();                  // Setup canvas (framebuffer) to start drawing
    BeginTextureMode(screenTexture); // Begin drawing to render texture

    // Render background with position set to textureScroll.
    DrawTextureEx(gameBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    // Render background again with position set to textureScroll + width of background. (this is to allow it to loop infinitely)
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
                DrawRectangle(rows * (gridSize + gridThickness) + 155, cols * (gridSize + gridThickness) + 155, gridSize, gridSize, (hoveredMove.column == cols && hoveredMove.row == rows) ? LIGHTGRAY : WHITE);
            }
        }
    }
    switch (checkWinner(board)) // Checks if there is a winner and draw text
    {
    case T: DrawText("Draw", 300, 675, 75, BLACK); break;
    case X: DrawText("Player X wins!", 145, 675, 75, BLACK); break;
    case O: DrawText("Player O wins!", 145, 675, 75, BLACK); break;
    }

    EndTextureMode(); // Ends drawing to render texture
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, 800, -800}, (Vector2){0, 0}, WHITE); // Draws the screen as a texture (easier unload)

    // Draw Home button
    DrawRectangleRounded((Rectangle){45, 45, 75, 75}, 0.2, 5, (homeHovered == 1) ? BLACK : GRAY);
    DrawTriangle((Vector2){25, 55}, (Vector2){140, 55}, (Vector2){82.5, 15}, (homeHovered == 1) ? BLACK : GRAY);

    EndDrawing(); // End canvas drawing
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Unloads the gameplay Screen, runs only once when called from helpers.c
 ---------------------------------------------------------------------------------------------------- */
void UnloadGameplayScreen() // Unload texture and render textures from GPU memory (VRAM)
{
    UnloadRenderTexture(screenTexture);
    UnloadTexture(gameBackground);
    UnloadRenderTexture(XTextures);     
    UnloadRenderTexture(OTextures);
}