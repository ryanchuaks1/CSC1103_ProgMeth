#include "../../include/tic-tac-toe.h"
#include "../../include/helpers.h"
#include "../../include/screens.h"

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

void UpdateGameplayScreen()
{
    // Move this out to a standalone function
    // Ideally make this function return a struct Move
    Vector2 gridVectors = (Vector2){155, 155};
    for (int rows = 0; rows < 3; rows++)
	{
		for (int cols = 0; cols < 3; cols++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){rows * (gridSize + gridThickness) + gridVectors.x, cols * (gridSize + gridThickness) + gridVectors.y, gridSize, gridSize}))
			{
                // On hover it will immediately place an X on the screen.
                board[rows][cols] = 'X';
			}
		}
	}
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
