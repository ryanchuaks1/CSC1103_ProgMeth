#include "../include/raylib.h"
//-----------------------------------------------------------------------------------------------------
//	Global Variables from screen_main
//-----------------------------------------------------------------------------------------------------
extern int currentScreen;
extern const int screenWidth, screenHeight;
extern int pressedButton;
extern char human;

//-----------------------------------------------------------------------------------------------------
//	Variables
//-----------------------------------------------------------------------------------------------------
// float textureScroll = 0.0f;
// int framesCounter = 0;					  // Variable to count frames (currently use for the main menu)
// const char gameTitle[64] = "Tic-Tac-Toe"; // Main title of the game
// int pressedButton = 0;

// Buttons
// Rectangle buttons[3] = {
// 	(Rectangle){250, 260, 300, 100},
// 	(Rectangle){250, 380, 300, 100},
// 	(Rectangle){250, 500, 300, 100}};

//-----------------------------------------------------------------------------------------------------
//	Render player select screen
//-----------------------------------------------------------------------------------------------------
void SelectPlayerScreen()
{
    RenderTexture2D screen = LoadRenderTexture(screenWidth, screenHeight);
    Texture2D menuBackground = LoadTexture("resources/menu_background.png");
    Sound gameStartSound = LoadSound("resources/game_start.wav");

    // Player selection
    pressedButton = checkButton(buttons);
    if ((pressedButton != -1) && IsMouseButtonPressed(0))
    {
        if (pressedButton == 0)
        {
            PlaySound(gameStartSound);
            human = 'X';
        }
        else if (pressedButton == 1)
        {
            PlaySound(gameStartSound);
            human = 'O';
        }
        else
        {
            PlaySound(gameStartSound);
            human = (char[2]){'X', 'O'}[random(2)];
        }
        // PlaySound(gameStartSound);
        currentScreen = 3;
    }

    BeginDrawing();
    BeginTextureMode(screen);
    // Render menuBackground and write header
    ClearBackground(WHITE);
    textureScroll -= 0.5f;
    DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);
    DrawText("Play As:", 250, 100, 75, BLACK);

    // Draw the buttons
    for (int i = 0; i < 3; i++)
    {
        DrawRectangleRounded(buttons[i], 0.2, 5, (pressedButton == i) ? BLACK : DARKGRAY);
        DrawRectangleRounded((Rectangle){buttons[i].x + 10, buttons[i].y + 10, 280, 80}, 0.2, 5, WHITE);
    }

    DrawText("X", 385, 288, 45, (pressedButton == 0) ? BLACK : DARKGRAY);
    DrawText("O", 385, 408, 45, (pressedButton == 1) ? BLACK : DARKGRAY);
    DrawText("Random", 320, 528, 45, (pressedButton == 2) ? BLACK : DARKGRAY);

    EndTextureMode();
    DrawTextureRec(screen.texture, (Rectangle){0, 0, screenWidth, -screenHeight}, (Vector2){0, 0}, WHITE);
    EndDrawing();
}