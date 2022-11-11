#include "../include/screens.h"
#include "../include/raylib.h"
#include "../include/helpers.h"
#include <stdio.h>

/** ----------------------------------------------------------------------------------------------------
 * Global Static Variables
 ---------------------------------------------------------------------------------------------------- */
// Static doesn't matter in this instances because we have an initialised function for each screens.
static RenderTexture2D screenTexture;
static Texture2D menuBackground;
static Sound gameStartSound;
static int checkButtonHovering = -1;

static Rectangle menuButton[3] = {
    (Rectangle){250, 260, 300, 100}, // Medium AI
    (Rectangle){250, 380, 300, 100}, // Impossible AI
    (Rectangle){250, 500, 300, 100}  // Back to Home
};
/** ----------------------------------------------------------------------------------------------------
 * @brief Initiate the Difficulty Screen, runs only once when navigating to the screen
 *
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void InitDifficultyScreen()
{
    checkButtonHovering = -1;

    screenTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    menuBackground = LoadTexture("resources/menu_background.png");
    gameStartSound = LoadSound("resources/game_start.wav");
}

void UpdateDifficultyScreen()
{
    textureScroll -= 0.5f;
    if (textureScroll <= -menuBackground.width * 2)
    {
        textureScroll = 0;
    }

    checkButtonHovering = checkButton(menuButton);
    if (checkButtonHovering == 0 && IsMouseButtonPressed(0))
    {
        PlaySound(gameStartSound);
        navigate(NormalAIMode);
    }
    else if (checkButtonHovering == 1 && IsMouseButtonPressed(0))
    {
        PlaySound(gameStartSound);
        navigate(ImpossibleAIMode);
    }
    else if (checkButtonHovering == 2 && IsMouseButtonPressed(0))
    {
        PlaySound(buttonClickSound);
        navigate(MainMenuScreen);
    }
}

void DrawDifficultyScreen()
{
    BeginDrawing();
    BeginTextureMode(screenTexture);

    ClearBackground(WHITE);
    DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawText("Select Difficulty", 85, 100, 75, BLACK);
    for (int i = 0; i < 3; i++)
    {
        DrawRectangleRounded(menuButton[i], 0.2, 5, (checkButtonHovering == i) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
        DrawRectangleRounded((Rectangle){menuButton[i].x + 10, menuButton[i].y + 10, 280, 80}, 0.2, 5, (Color){254, 215, 136, 255});
    }
    DrawText("Medium", 330, 288, 45, (checkButtonHovering == 0) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("Impossible", 292, 408, 45, (checkButtonHovering == 1) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("Home", 350, 528, 45, (checkButtonHovering == 2) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});

    EndTextureMode();
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, GetScreenWidth(), -GetScreenHeight()}, (Vector2){0, 0}, WHITE);
    EndDrawing();
}

void UnloadDifficultyScreen()
{
    UnloadRenderTexture(screenTexture);
    UnloadTexture(menuBackground);
}