#include "../include/raylib.h"
#include "../../include/helpers.h"
#include "../../include/screens.h"

#include <stdio.h>

static int finishExitCode = -1;
static RenderTexture2D screen;
static Texture2D menuBackground;
static Sound buttonClickSound;
static int checkButtonHovering = -1;

// TODO : Remove 1 of them as we only have 2 buttons
static Rectangle menuButton[3] = {
    (Rectangle){250, 260, 300, 100}, // Medium AI
	(Rectangle){250, 380, 300, 100}, // Impossible AI
	(Rectangle){250, 500, 300, 100}  // Back to Home
};

void InitDifficultyScreen()
{
    printf("Initializing difficulty screen");
    printf("Button hover score is: %d", checkButtonHovering);
    checkButtonHovering = -1;
}

void UpdateDifficultyScreen()
{
    checkButtonHovering = checkButton(menuButton);
}

void DrawDifficultyScreen()
{
    BeginDrawing();

    ClearBackground(WHITE);
    DrawText("Select Difficulty", 85, 100, 75, BLACK);
    for (int i = 0; i < 3; i++)
	{
		DrawRectangleRounded(menuButton[i], 0.2, 5, (checkButtonHovering == i) ? BLACK : DARKGRAY);
		DrawRectangleRounded((Rectangle){menuButton[i].x + 10, menuButton[i].y + 10, 280, 80}, 0.2, 5, WHITE);
	}
	DrawText("Medium", 345, 288, 45, (checkButtonHovering == 0) ? BLACK : DARKGRAY);
	DrawText("Impossible", 292, 408, 45, (checkButtonHovering == 1) ? BLACK : DARKGRAY);
	DrawText("Home", 350, 528, 45, (checkButtonHovering == 2) ? BLACK : DARKGRAY);

    EndDrawing();
}

void UnloadDifficultyScreen()
{
}

/// @brief 
/// @return (1 = Easy AI), (2 = Impossible AI)
int FinishDifficultyScreen()
{
    return finishExitCode;
}