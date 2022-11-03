#include "../include/raylib.h"
//-----------------------------------------------------------------------------------------------------
//	Global Variables from screen_main
//-----------------------------------------------------------------------------------------------------
extern int currentScreen;
extern const int screenWidth, screenHeight;
extern int pressedButton;
extern char gameMode;

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
//	Render select difficulty screen
//-----------------------------------------------------------------------------------------------------
void SelectDifficultyScreen()
{
	RenderTexture2D screen = LoadRenderTexture(screenWidth, screenHeight);
	Texture2D menuBackground = LoadTexture("resources/menu_background.png");
	Sound buttonClickSound = LoadSound("resources/button_click.wav");

	pressedButton = checkButton(buttons);
	// Check which difficulty was selected
	if ((pressedButton == 0 || pressedButton == 1) && IsMouseButtonPressed(0))
	{
		PlaySound(buttonClickSound);
		gameMode = pressedButton == 0 ? '1' : '2';
		currentScreen = 2;
	}
	else if (pressedButton == 2 && IsMouseButtonPressed(0))
	{ // Go back to the home screen
		PlaySound(buttonClickSound);
		currentScreen = 0;
	}

	BeginDrawing();
	BeginTextureMode(screen);

	// Render menuBackground and write header
	ClearBackground(WHITE);
	textureScroll -= 0.5f;
	if (textureScroll <= -menuBackground.width * 2)
		textureScroll = 0;
	DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
	DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);

	DrawText("Select Difficulty", 85, 100, 75, BLACK);
	// Draw the buttons
	for (int i = 0; i < 3; i++)
	{
		DrawRectangleRounded(buttons[i], 0.2, 5, (pressedButton == i) ? BLACK : DARKGRAY);
		DrawRectangleRounded((Rectangle){buttons[i].x + 10, buttons[i].y + 10, 280, 80}, 0.2, 5, WHITE);
	}
	DrawText("Easy", 345, 288, 45, (pressedButton == 0) ? BLACK : DARKGRAY);
	DrawText("Impossible", 292, 408, 45, (pressedButton == 1) ? BLACK : DARKGRAY);
	DrawText("Home", 350, 528, 45, (pressedButton == 2) ? BLACK : DARKGRAY);
	EndTextureMode();

	DrawTextureRec(screen.texture, (Rectangle){0, 0, screenWidth, -screenHeight}, (Vector2){0, 0}, WHITE);
	EndDrawing();
}