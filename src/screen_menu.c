#include "../include/raylib.h"
//-----------------------------------------------------------------------------------------------------
//	Global Variables from screen_main
//-----------------------------------------------------------------------------------------------------
extern int currentScreen;
extern const int screenWidth, screenHeight;
extern int pressedButton;

//-----------------------------------------------------------------------------------------------------
//	Global Variables? at this point idk anymore
//-----------------------------------------------------------------------------------------------------
float textureScroll = 0.0f;
int framesCounter = 0;					  // Variable to count frames (currently use for the main menu)
const char gameTitle[64] = "Tic-Tac-Toe"; // Main title of the game
Rectangle buttons[3] = {
	(Rectangle){250, 260, 300, 100},
	(Rectangle){250, 380, 300, 100},
	(Rectangle){250, 500, 300, 100}};

//-----------------------------------------------------------------------------------------------------
//	Render main menu screen
//-----------------------------------------------------------------------------------------------------
void MainMenuScreen()
{
	RenderTexture2D screen = LoadRenderTexture(screenWidth, screenHeight);
	Texture2D menuBackground = LoadTexture("resources/menu_background.png");
	Sound buttonClickSound = LoadSound("resources/button_click.wav");
	Sound gameStartSound = LoadSound("resources/game_start.wav");

	pressedButton = checkButton(buttons);
	if ((pressedButton == 0) && IsMouseButtonPressed(0)) // Two player is clicked
	{
		PlaySound(gameStartSound);
		currentScreen = 3; // Move to game screen
	}
	else if ((pressedButton == 1) && IsMouseButtonPressed(0)) // VS AI is clicked
	{
		PlaySound(buttonClickSound);
		currentScreen = 1; // Move to select difficulty
	}
	else if (pressedButton == 2 && IsMouseButtonPressed(0))
	{
		currentScreen = 4;
	}

	BeginDrawing(); // Setup canvas (framebuffer) to start drawing
	BeginTextureMode(screen);

	// Render Menu Background and write header
	ClearBackground(WHITE);
	textureScroll -= 0.5f;
	if (textureScroll <= -menuBackground.width * 2)
		textureScroll = 0;
	DrawTextureEx(menuBackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
	DrawTextureEx(menuBackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);

	// TextSubtext() Gets a piece of a text string
	// @params *text, starting position, speed);
	framesCounter++;
	DrawText(TextSubtext(gameTitle, 0, framesCounter / 4), 100, 60, 90, BLACK);

	// Draw the buttons
	for (int i = 0; i < 3; i++)
	{
		// rectangle(already declared initially), roundness, segments, color
		DrawRectangleRounded(buttons[i], 0.2, 5, (pressedButton == i) ? BLACK : DARKGRAY);				 // Border
		DrawRectangleRounded((Rectangle){buttons[i].x + 10, buttons[i].y + 10, 280, 80}, 0.2, 5, WHITE); // Text
	}

	// Draw text into the buttons
	DrawText("Two Player", 275, 288, 45, (pressedButton == 0) ? BLACK : DARKGRAY);
	DrawText("Vs AI", 330, 408, 45, (pressedButton == 1) ? BLACK : DARKGRAY);
	DrawText("Exit", 360, 528, 45, (pressedButton == 2) ? BLACK : DARKGRAY);
	EndTextureMode(); // End canvas drawing and swap buffers (double buffering)

	DrawTextureRec(screen.texture, (Rectangle){0, 0, screenWidth, -screenHeight}, (Vector2){0, 0}, WHITE);
	EndDrawing();
}
