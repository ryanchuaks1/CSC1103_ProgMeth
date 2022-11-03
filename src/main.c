#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/raylib.h"
#include "../headers/functions.h"
#include "screen_menu.c"
#include "screen_difficulty.c"
#include "screen_selectplayer.c"

//-----------------------------------------------------------------------------------------------------
//	Global variables
//-----------------------------------------------------------------------------------------------------
int pressedButton;
int currentScreen;
const int screenWidth = 800, screenHeight = 800;
char gameMode = '0';
char human = 'X';

int mouseCollide(Vector2 mousePos, Vector2 gridPos, int gridSize, int gridThickness);
int checkButton(Rectangle buttons[3]);

int main(void)
{
	// char grid[9];
	// resetGrid(grid);
	// char playerTurn = 'X';
	// char winChecker = 0;
	// int emptySpaces = 9;
	// int grid_index;
	// int gameState = 0;

	// Screen
	InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
	SetTargetFPS(60); // Sets the FPS of the program

	// Audio
	InitAudioDevice();												  // Initialize audio device
	Sound backgroundMusic = LoadSound("resources/fall-music.wav");	  // Load button sound
	SetSoundVolume(backgroundMusic, 0.5); // TODO: volume buttons?
	PlaySound(backgroundMusic);			  // Start playing background music

	// // Game
	// const int gridSize = 150, gridThickness = 10; // gridSize is the grid size, gridThickness is the thickness of grid lines
	// const int timer = 4 * 60;					  // Number of seconds to delay * frame rate
	// int counter = 0;							  // Counter for the game to restart

	// RenderTexture2D X = LoadRenderTexture(gridSize, gridSize); // Load texture for rendering (framebuffer)
	// RenderTexture2D O = LoadRenderTexture(gridSize, gridSize); // Load texture for rendering (framebuffer)

	// BeginTextureMode(X);	// Begin drawing to render texture X
	// ClearBackground(WHITE); // Background color of the X
	// // (posX, posY, height, width)
	// DrawRectanglePro((Rectangle){35, 13, gridSize - 5, 25}, (Vector2){0, 0}, 45.0f, RED);
	// DrawRectanglePro((Rectangle){135, 30, gridSize - 5, 25}, (Vector2){0, 0}, 135.0f, RED);
	// EndTextureMode(); // Ends drawing to render texture

	// BeginTextureMode(O);	// Begin drawing to render texture O
	// ClearBackground(WHITE); // Background color of the O
	// // (posX, posY, radius, color)
	// DrawCircle(gridSize / 2, gridSize / 2, gridSize / 2 - 5, BLUE); // Outer circle
	// DrawCircle(gridSize / 2, gridSize / 2, 45, WHITE);				// Inner Circle
	// EndTextureMode();												// Ends drawing to render texture

	// Main gameplay loop
	currentScreen = 0;
	while (!WindowShouldClose()) // WindowShould Close checks if ESC key is pressed
	{
		switch (currentScreen) // When the variable of currentScreen changes, it will change screen accordingly
		{
		case 0: MainMenuScreen(); break;
		case 1: SelectDifficultyScreen(); break;
		case 2: SelectPlayerScreen(); break;
		case 4:
		{
			//UnloadSound(buttonClickSound); // Unload sounds
			//UnloadSound(gameStartSound);
			//UnloadSound(gameOverSound);
			//UnloadSound(backgroundMusic);
			//UnloadSound(placeTokenSound);
			//CloseAudioDevice(); // Close audio device
			//
			//UnloadRenderTexture(screen);   // Unload screen texture
			//UnloadTexture(menuBackground); // Unload menuBackground texture
			//UnloadTexture(gamebackground); // Unload menuBackground texture
			//UnloadRenderTexture(X);
			//UnloadRenderTexture(O);

			CloseWindow();
		}
			return 0;

			// case 3:
			// 	// Main game
			// 	switch (gameState)
			// 	{
			// 	case 0:
			// 		grid_index = mouseCollide(GetMousePosition(), (Vector2){155, 155}, gridSize, gridThickness);
			// 		if ((gameMode == '0' || human == playerTurn))
			// 		{
			// 			if (IsMouseButtonPressed(0) && grid_index != -1 && grid[grid_index] == ' ')
			// 			{
			// 				PlaySound(placeTokenSound);
			// 				grid[grid_index] = playerTurn; // Place the player token on the grid
			// 				playerTurn = switchPlayer(playerTurn);
			// 				emptySpaces--;
			// 			}
			// 		}
			// 		else if (human != playerTurn)
			// 		{
			// 			if (gameMode == '1')
			// 			{
			// 				normalAI(grid, playerTurn, emptySpaces);
			// 			}
			// 			else
			// 			{
			// 				impossibleAI(grid, playerTurn, emptySpaces);
			// 			}
			// 			playerTurn = switchPlayer(playerTurn);
			// 			emptySpaces--;
			// 		}

			// 		if (checkWinner('X', grid) == 1)
			// 		{
			// 			winChecker = 'X';
			// 			gameState = 1;
			// 		}
			// 		else if (checkWinner('O', grid) == 1)
			// 		{
			// 			winChecker = 'O';
			// 			gameState = 1;
			// 		}
			// 		else if (emptySpaces == 0)
			// 		{
			// 			winChecker = '0';
			// 			gameState = 1;
			// 		}
			// 		break;

			// 	case 1:
			// 		// Delay the game for some time after a win and show counter
			// 		if (counter >= timer)
			// 		{
			// 			PlaySound(gameOverSound);
			// 			gameState = 2;
			// 			counter = 0;
			// 		}
			// 		else
			// 		{
			// 			counter++;
			// 		}
			// 		break;

			// 	case 2:
			// 		if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){25, 15, 115, 105}))
			// 			pressedButton = 1;

			// 		// Drawing the game screen and main grid
			// 		BeginDrawing();
			// 		BeginTextureMode(screen);
			// 		// Render Game background
			// 		ClearBackground(WHITE);
			// 		textureScroll -= 0.5f;
			// 		DrawTextureEx(gamebackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
			// 		DrawTextureEx(gamebackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);

			// 		DrawRectangle(145, 145, (gridSize * 3 + gridThickness * 2) + 20, (gridSize * 3 + gridThickness * 2) + 20, BLACK); // 150, 20
			// 		for (int i = 0; i < 3; i++)
			// 		{
			// 			for (int j = 0; j < 3; j++)
			// 			{
			// 				if (grid[j * 3 + i] != ' ')
			// 				{
			// 					DrawTextureRec((grid[j * 3 + i] == 'X') ? X.texture : O.texture, (Rectangle){0, 0, gridSize, -gridSize}, (Vector2){i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155}, WHITE);
			// 				}
			// 				else
			// 				{
			// 					if (CheckCollisionPointRec((Vector2){GetMouseX(), GetMouseY()}, (Rectangle){i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize}))
			// 					{
			// 						DrawRectangle(i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize, LIGHTGRAY);
			// 					}
			// 					else
			// 					{
			// 						DrawRectangle(i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize, WHITE);
			// 					}
			// 				}
			// 			}
			// 		}

			// 		switch (winChecker)
			// 		{
			// 		case 'X':
			// 			DrawText("Player X wins!", 145, 675, 75, BLACK);
			// 			break;
			// 		case 'O':
			// 			DrawText("Player O wins!", 145, 675, 75, BLACK);
			// 			break;
			// 		case '0':
			// 			DrawText("Draw", 300, 675, 75, BLACK);
			// 			break;
			// 		}
			// 		EndTextureMode();
			// 		DrawTextureRec(screen.texture, (Rectangle){0, 0, screenWidth, -screenHeight}, (Vector2){0, 0}, WHITE);
			// 		// Home button
			// 		DrawRectangleRounded((Rectangle){45, 45, 75, 75}, 0.2, 5, (pressedButton == 1) ? BLACK : GRAY);
			// 		DrawTriangle((Vector2){25, 55}, (Vector2){140, 55}, (Vector2){82.5, 15}, (pressedButton == 1) ? BLACK : GRAY);
			// 		EndDrawing();

			// 		// Exit to the home screen if the home button is pressed
			// 		if ((pressedButton == 1) && IsMouseButtonPressed(0))
			// 		{
			// 			resetGrid(grid);
			// 			gameMode = '0';
			// 			winChecker = 0;
			// 			gameState = 0;
			// 			playerTurn = 'X';
			// 			emptySpaces = 9;
			// 			currentScreen = 0;
			// 		}

			// 		break;
			// 	} // Reset the game
			// 	resetGrid(grid);
			// 	winChecker = 0;
			// 	gameState = 0;
			// 	playerTurn = 'X';
			// 	emptySpaces = 9;
			// 	break;
		}

		pressedButton = -1;
	}
}

int mouseCollide(Vector2 mousePos, Vector2 gridPos, int gridSize, int gridThickness)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CheckCollisionPointRec(mousePos, (Rectangle){i * (gridSize + gridThickness) + gridPos.x, j * (gridSize + gridThickness) + gridPos.y, gridSize, gridSize}))
			{
				return j * 3 + i;
			}
		}
	}

	return -1;
}

int checkButton(Rectangle buttons[3])
{
	Vector2 mousePos = GetMousePosition(); // Gets the current mouse position
	for (int i = 0; i < 3; i++)
	{
		if (CheckCollisionPointRec(mousePos, buttons[i])) // Check is there are any mouse collisions with rectangles (in this case buttons)
			return i;
	}

	return -1;
}
