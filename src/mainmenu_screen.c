#include "../include/screens.h"
#include "../include/raylib.h"
#include "../include/helpers.h"
#include <stdio.h>

/** ----------------------------------------------------------------------------------------------------
 * Local Variables
 ---------------------------------------------------------------------------------------------------- */
// Static doesn't matter in this instances because we have an initialised function for each screens.
static RenderTexture2D screenTexture;
static Texture2D menuBackground;
static Sound buttonClickSound;
static Sound gameStartSound;

static int framesCounter;
static int checkButtonHovering;

static Rectangle menuButton[3] = {
    (Rectangle){250, 260, 300, 100}, // Multiplayer
    (Rectangle){250, 380, 300, 100}, // VS AI
    (Rectangle){250, 500, 300, 100}  // Exit
};

/** ----------------------------------------------------------------------------------------------------
 * @brief Initiate the Main Menu Screen, runs only once when navigating to the screen
 *
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void InitMainMenuScreen()
{
    framesCounter = 0;        // Sets the frame counter to 0 (This is used for animating text)
    checkButtonHovering = -1; // Sets the default button hover to -1 which is nothing/default

    screenTexture = LoadRenderTexture(800, 800);                   // Load texture for rendering
    menuBackground = LoadTexture("resources/menu_background.png"); // Load background image
    buttonClickSound = LoadSound("resources/button_click.wav");    // Load button click sound
    gameStartSound = LoadSound("resources/game_start.wav");        // Load game start sound
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Initiate the Main Menu Screen, runs only once when navigating to the screen from main.c
 *
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void UpdateMainMenuScreen()
{
    // Check which button is being hoverd on and return its index. CheckButton() exists in helpers.c
    checkButtonHovering = checkButton(menuButton);
    if ((checkButtonHovering == 0) && IsMouseButtonPressed(0)) // Checks if button is hovered on and mouse is clicked
    {
        PlaySound(gameStartSound); // Play game start sound
        navigate(MultiplayerMode);
    }
    else if ((checkButtonHovering == 1) && IsMouseButtonPressed(0)) // Checks if button is hovered on and mouse is clicked
    {
        PlaySound(buttonClickSound); // Play button click sound
        navigate(DifficultyScreen);
    }
    else if ((checkButtonHovering == 2) && IsMouseButtonPressed(0)) // Checks if button is hovered on and mouse is clicked
    {
        UnloadMainMenuScreen();
        CloseWindow(); // Return exit code 1, "close window" in main.c
    }

    textureScroll -= 0.5f;                          // -0.5 pixels in position to the background texture
    if (textureScroll <= -menuBackground.width * 2) // Checks if background texture position exceeds the width of the image
    {
        textureScroll = 0; // Resets background texture back to original position creating a loop
    }
    framesCounter++; // Allow the text title to slowly pop out on the screen by counting frames
}

/** ----------------------------------------------------------------------------------------------------
 * @brief DrawMainMenuScreen is continuously looping while the programm is still running (window is not close)
 * This loop is created from main.c in the UpdateDrawFrame() function
 * Since FPS of program is set to 60 in main.c, this function loops about 60 times a second
 *
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void DrawMainMenuScreen()
{
    BeginDrawing();                  // Setup canvas (framebuffer) to start drawing
    BeginTextureMode(screenTexture); // Begin drawing to render texture

    // Render background with position set to textureScroll.
    DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    // Render background with position set to textureScroll + width of background.
    DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);

    DrawText(TextSubtext("Tic-Tac-Toe", 0, framesCounter / 4), 100, 60, 90, BLACK);
    for (int i = 0; i < 3; i++)
    {
        // rectangle(already declared initially), roundness, segments, color
        DrawRectangleRounded(menuButton[i], 0.2, 5, (checkButtonHovering == i) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255}); // Border
        DrawRectangleRounded((Rectangle){menuButton[i].x + 10, menuButton[i].y + 10, 280, 80}, 0.2, 5, (Color){254, 215, 136, 255});     // Background
    }
    DrawText("Two Player", 275, 288, 45, (checkButtonHovering == 0) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("Vs AI", 330, 408, 45, (checkButtonHovering == 1) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});
    DrawText("Exit", 360, 528, 45, (checkButtonHovering == 2) ? (Color){226, 122, 61, 255} : (Color){90, 49, 24, 255});

    EndTextureMode();
    DrawTextureRec(screenTexture.texture, (Rectangle){0, 0, 800, -800}, (Vector2){0, 0}, WHITE);
    EndDrawing();
}

void UnloadMainMenuScreen()
{
    UnloadRenderTexture(screenTexture);
    UnloadTexture(menuBackground);
}