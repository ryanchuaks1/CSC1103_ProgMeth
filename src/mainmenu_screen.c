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
static int framesCounter;
static int checkButtonHovering;
extern bool exitWindowRequested;

static Rectangle menuButton[3] = {
    (Rectangle){205, 260, 390, 100}, // Multiplayer
    (Rectangle){205, 380, 390, 100}, // VS AI
    (Rectangle){205, 500, 390, 100}  // Exit
};

/** ----------------------------------------------------------------------------------------------------
 * @brief Initiate the Main Menu Screen, runs only once when navigating to the screen
 *
 * @date mainmenu_screen.c last updated 19/11/2022
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void InitMainMenuScreen()
{
    framesCounter = 0;        // Sets the frame counter to 0 (This is used for animating text)
    checkButtonHovering = -1; // Sets the default button hover to -1 which is nothing/default

    screenTexture = LoadRenderTexture(800, 800);                   // Load texture for rendering
    menuBackground = LoadTexture("resources/menu_background.png"); // Load background image
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Updates the main menu screen screen parameters. This function runs about 60 times a second.
 * This loop is created from main.c in the UpdateDrawFrame() function
 * This function checks if a button is hovered using @param checkButtonHovering. This also checks
 * if the user clicks on one of the buttons
 ---------------------------------------------------------------------------------------------------- */
void UpdateMainMenuScreen()
{
    // Check which button is being hoverd on and return its index. CheckButton() exists in helpers.c
    checkButtonHovering = checkButton(menuButton);
    if ((checkButtonHovering == 0) && IsMouseButtonPressed(0)) // Checks if button is hovered on and mouse is clicked
    {
        PlaySound(gameStartSound); // Play game start sound
        navigate(MultiplayerMode); // Navigate to Multiplayer mode and respective screen
    }
    else if ((checkButtonHovering == 1) && IsMouseButtonPressed(0)) // Checks if button is hovered on and mouse is clicked
    {
        PlaySound(buttonClickSound); // Play button click sound
        navigate(DifficultyScreen);  // Navigate to select difficulty mode and respective screen
    }
    else if ((checkButtonHovering == 2) && IsMouseButtonPressed(0)) // Checks if button is hovered on and mouse is clicked
    {
        exitWindowRequested = true; // If the user hits exit, unload current screen
    }

    textureScroll -= 0.5f;                          // -0.5 pixels in position to the background texture
    if (textureScroll <= -menuBackground.width * 2) // Checks if background texture position exceeds the width of the image
    {
        textureScroll = 0; // Resets background texture back to original position creating a loop
    }
    framesCounter++; // Allow the text title to slowly pop out on the screen by counting frames
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Updates the main menu screen screen user interface. This function runs about 60 times a second.
 * This loop is created from main.c in the UpdateDrawFrame() function
 * This function renders the next frame of the program and renders it into the screen.
 ---------------------------------------------------------------------------------------------------- */
void DrawMainMenuScreen()
{
    BeginDrawing();                  // Setup canvas (framebuffer) to start drawing
    BeginTextureMode(screenTexture); // Begin drawing to render texture

    // Render background with position set to textureScroll.
    DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    // Render background again with position set to textureScroll + width of background. (this is to allow it to loop infinitely)
    DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);

    DrawText(TextSubtext("Tic-Tac-Toe", 0, framesCounter / 4), 100, 60, 90, BLACK);
    for (int i = 0; i < 3; i++)
    {
        // rectangle(already declared initially), roundness, segments, color
        DrawRectangleRounded(menuButton[i], 0.2, 5, (checkButtonHovering == i) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255}); // Border
        DrawRectangleRounded((Rectangle){menuButton[i].x + 10, menuButton[i].y + 10, 280, 80}, 0.2, 5, (Color){254, 215, 136, 255});     // Background
        DrawRectangleRounded((Rectangle){505, menuButton[i].y + 10, 80, 80}, 0.2, 5, (Color){254, 215, 136, 255});                       // Background 2
    }
    DrawText("Two Player", 230, 288, 45, (checkButtonHovering == 0) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("2P", 520, 288, 45, (checkButtonHovering == 0) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});

    DrawText("Vs AI", 290, 408, 45, (checkButtonHovering == 1) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("1P", 525, 408, 45, (checkButtonHovering == 1) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});

    DrawText("Exit", 320, 528, 45, (checkButtonHovering == 2) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("X", 532, 528, 45, (checkButtonHovering == 2) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});

    EndTextureMode(); // Ends drawing to render texture
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, 800, -800}, (Vector2){0, 0}, WHITE); // Draws the screen as a texture (easier unload)
    EndDrawing(); // End canvas drawing
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Unloads the Main Menu Screen, runs only once when called from helpers.c
 ---------------------------------------------------------------------------------------------------- */
void UnloadMainMenuScreen()
{
    UnloadRenderTexture(screenTexture); // Unload render texture from GPU memory (VRAM)
    UnloadTexture(menuBackground);      // Unload texture from GPU memory (VRAM)
}