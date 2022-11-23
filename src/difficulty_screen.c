#include "../include/screens.h"
#include "../include/raylib.h"
#include "../include/helpers.h"
#include <stdio.h>

/** ----------------------------------------------------------------------------------------------------
 * Global Static Variables
 ---------------------------------------------------------------------------------------------------- */
// Static keeps the variables local to this file.
static RenderTexture2D screenTexture;
static Texture2D menuBackground;
static int checkButtonHovering;

static Rectangle menuButton[3] = {
    (Rectangle){250, 260, 300, 100}, // Easy AI
    (Rectangle){250, 380, 300, 100}, // Impossible AI
    (Rectangle){250, 500, 300, 100}  // Back to Home
};
/** ----------------------------------------------------------------------------------------------------
 * @brief Initiate the Difficulty Screen, runs only once when navigating to the screen
 *
 * @date difficulty_screen.c last updated 19/11/2022
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void InitDifficultyScreen()
{
    checkButtonHovering = -1;

    screenTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    menuBackground = LoadTexture("resources/menu_background.png");
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Updates the difficulty screen parameters. This function runs about 60 times a second.
 * This loop is created from main.c in the UpdateDrawFrame() function
 * This function checks if a button is hovered using @param checkButtonHovering. This also checks
 * if the user clicks on one of the buttons
 ---------------------------------------------------------------------------------------------------- */
void UpdateDifficultyScreen()
{
    checkButtonHovering = checkButton(menuButton);
    if (checkButtonHovering == 0 && IsMouseButtonPressed(0))
    {
        PlaySound(gameStartSound);
        navigate(EasyAIMode);
    }
    else if (checkButtonHovering == 1 && IsMouseButtonPressed(0))
    {
        PlaySound(gameStartSound);
        navigate(MediumAIMode);
    }
    else if (checkButtonHovering == 2 && IsMouseButtonPressed(0))
    {
        PlaySound(gameStartSound);
        navigate(ImpossibleAIMode);
    }
    textureScroll -= 0.5f;
    if (textureScroll <= -menuBackground.width * 2)
    {
        textureScroll = 0;
    }
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Updates the difficulty screen user interface. This function runs about 60 times a second.
 * This loop is created from main.c in the UpdateDrawFrame() function
 * This function renders the next frame of the program and renders it into the screen.
 ---------------------------------------------------------------------------------------------------- */
void DrawDifficultyScreen()
{
    BeginDrawing();                  // Setup canvas (framebuffer) to start drawing
    BeginTextureMode(screenTexture); // Begin drawing to render texture

    DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawText("Select Difficulty", 85, 100, 75, BLACK);
    for (int i = 0; i < 3; i++)
    {
        // rectangle(already declared initially), roundness, segments, color
        DrawRectangleRounded(menuButton[i], 0.2, 5, (checkButtonHovering == i) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255}); // Border
        DrawRectangleRounded((Rectangle){menuButton[i].x + 10, menuButton[i].y + 10, 280, 80}, 0.2, 5, (Color){254, 215, 136, 255});     // Background
    }
    DrawText("Easy", 345, 288, 45, (checkButtonHovering == 0) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("Medium", 325, 408, 45, (checkButtonHovering == 1) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("Impossible", 290, 528, 45, (checkButtonHovering == 2) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});

    EndTextureMode();                                                                                                       // Ends drawing to render texture
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, GetScreenWidth(), -GetScreenHeight()}, (Vector2){0, 0}, WHITE); // Draws the screen as a texture (easier unload)
    EndDrawing();                                                                                                           // End canvas drawing
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Unloads the difficulty Screen, runs only once when called from helpers.c
 ---------------------------------------------------------------------------------------------------- */
void UnloadDifficultyScreen()
{
    UnloadRenderTexture(screenTexture); // Unload render texture from GPU memory (VRAM)
    UnloadTexture(menuBackground);      // Unload texture from GPU memory (VRAM)
}