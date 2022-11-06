#include "../../include/screens.h"
#include "../../include/raylib.h"
#include "../../include/helpers.h"

// Static doesn't matter in this instances because we have an initialised function for each screens.
static RenderTexture2D screenTexture;
static Texture2D menuBackground;
static Sound buttonClickSound;
static Sound gameStartSound;
static float textureScroll;
static int framesCounter;
static int checkButtonHovering;

static int finishExitCode = -1;

static Rectangle menuButton[3] = {
    (Rectangle){250, 260, 300, 100}, // Multiplayer
	(Rectangle){250, 380, 300, 100}, // VS AI
	(Rectangle){250, 500, 300, 100}  // Exit
};

void InitMainMenuScreen()
{
    finishExitCode = -1;

    textureScroll = 0.0f;
    framesCounter = 0;
    checkButtonHovering = -1;

    screenTexture = LoadRenderTexture(800, 800);
    menuBackground = LoadTexture("../resources/menu_background.png");

    buttonClickSound = LoadSound("../resources/button_click.wav");
    gameStartSound = LoadSound("../resources/button_click.wav");
}

void UpdateMainMenuScreen()
{
    checkButtonHovering = checkButton(menuButton);
    // Hovering is not enough we need to click it then we can attempt to call FinishMainMenu with an exit code.
    if ((checkButtonHovering == 0) && IsMouseButtonPressed(0))
    {
        PlaySound(gameStartSound);
        finishExitCode = 1;
    }
    else if ((checkButtonHovering == 1) && IsMouseButtonPressed(0))
    {
        PlaySound(buttonClickSound);
        finishExitCode = 2;
    }
    else if ((checkButtonHovering == 1) && IsMouseButtonPressed(0))
    {
        finishExitCode = 3;
    }

    // Variable that checks for texture so that the background can scroll
    textureScroll -= 0.5f;
	if (textureScroll <= -menuBackground.width * 2)
    {
		textureScroll = 0;
    }

    // Allow the text title to slowly pop out on the screen
    framesCounter++;
}

// Texture is currently not working. My guess is that the file path is wrong/
void DrawMainMenuScreen()
{
    BeginDrawing(); // Setup canvas (framebuffer) to start drawing
	BeginTextureMode(screenTexture);

    ClearBackground(WHITE);
    DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
	DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawText(TextSubtext("Tic-Tac-Toe", 0, framesCounter / 4), 100, 60, 90, BLACK);
	for (int i = 0; i < 3; i++)
	{
		// rectangle(already declared initially), roundness, segments, color
		DrawRectangleRounded(menuButton[i], 0.2, 5, (checkButtonHovering == i) ? BLACK : DARKGRAY);				 // Border
		DrawRectangleRounded((Rectangle){menuButton[i].x + 10, menuButton[i].y + 10, 280, 80}, 0.2, 5, WHITE); // Text
	}
	DrawText("Two Player", 275, 288, 45, (checkButtonHovering == 0) ? BLACK : DARKGRAY);
	DrawText("Vs AI", 330, 408, 45, (checkButtonHovering == 1) ? BLACK : DARKGRAY);
	DrawText("Exit", 360, 528, 45, (checkButtonHovering == 2) ? BLACK : DARKGRAY);

    EndTextureMode();
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, 800, -800}, (Vector2){0, 0}, WHITE);
    EndDrawing();
}

void UnloadMainMenuScreen()
{
}

/// @brief Returns an exit code which indicates which screen to goto next.
/// @return 1 = Multiplayer, 2 = VS AI (Redirects to DifficultyScreenMode)
int FinishMainMenuScreen()
{
    return finishExitCode;
}