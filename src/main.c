#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/raylib.h"
#include "../headers/functions.h"

int mouseCollide(Vector2 mousePos, Vector2 gridPos, int gridSize, int gridThickness);
int checkButton(Rectangle buttons[3]);

/**
 *
 *	@brief Main function of the program
 *
 * 	This is a tic tac toe game powered by raylib
 * 	The main menu UI consist of 3 buttons, 1p mode 2p mode and exit button
 *
 * 	@authors Ryan, Kang Le, Clarissa, Xavier, Sean
 *
 */
int main(void)
{
	// Definitions of gameplay variables
	char grid[9];
	/** resetGrid is defined under @file headers/functions.h */
	// This function clears the grid
	resetGrid(grid);

	// Value of X represents player 1's turn, value of O represents player 2's turn
	char playerTurn = 'X';
	char human = 'X';
	// srand(time(0));

	// Used when determining who won for the output
	char winChecker = 0;

	int emptySpaces = 9;
	int grid_index;

	// This variable checks the game state
	// 0 means the game is still going on
	// 1 means the game is on delay
	// 2 means the game is over
	int gameState = 0;

	// This variable checks the game
	// 0 for 2 players,
	// 1 for normal AI,
	// 2 for impossible AI mode
	char gameMode = '0';

	// 0 = Home
	// 1 = Difficulty
	// 2 = Player selection
	// 3 = Main game
	int currentScreen = 0;

	// Main windows init
	// Screen
	const int screenWidth = 800, screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
	SetTargetFPS(60); // Sets the FPS of the program
	Texture2D menuBackground = LoadTexture("resources/menu_background.png");
	Texture2D gamebackground = LoadTexture("resources/game_background.png");
	float textureScroll = 0.0f;
	int framesCounter = 0;					  // Variable to count frames (currently use for the main menu)
	const char gameTitle[64] = "Tic-Tac-Toe"; // Main title of the game

	// Audio
	InitAudioDevice();												  // Initialize audio device
	Sound backgroundMusic = LoadSound("resources/fall-music.wav");	  // Load button sound
	Sound buttonClickSound = LoadSound("resources/button_click.wav"); // Load button sound
	Sound gameStartSound = LoadSound("resources/game_start.wav");	  // Load button sound
	Sound gameOverSound = LoadSound("resources/game_over.wav");		  // Load button sound
	Sound placeTokenSound = LoadSound("resources/place_token.wav");	  // Load button sound

	SetSoundVolume(backgroundMusic, 0.5); // TODO: volume buttons?
	PlaySound(backgroundMusic);			  // Start playing background music

	// Game
	const int gridSize = 150, gridThickness = 10; // gridSize is the grid size, gridThickness is the thickness of grid lines
	const int timer = 4 * 60;					  // Number of seconds to delay * frame rate
	int counter = 0;							  // Counter for the game to restart

	int pressedButton;

	/**
	 *
	 *	@brief Draw the all the textures
	 * 	@param RenderTexture2D
	 * 	@param BeginTextureMode
	 * 	@param ClearBackground
	 * 	@param DrawRectanglePro
	 * 	@param DrawCircle
	 * 	@param EndTextureMode
	 *  refer to https://www.raylib.com/cheatsheet/cheatsheet.html
	 *
	 * 	@authors
	 *
	 */
	RenderTexture2D screen = LoadRenderTexture(screenWidth, screenHeight);
	RenderTexture2D X = LoadRenderTexture(gridSize, gridSize); // Load texture for rendering (framebuffer)
	RenderTexture2D O = LoadRenderTexture(gridSize, gridSize); // Load texture for rendering (framebuffer)

	BeginTextureMode(X);	// Begin drawing to render texture X
	ClearBackground(WHITE); // Background color of the X
	// (posX, posY, height, width)
	DrawRectanglePro((Rectangle){35, 13, gridSize - 5, 25}, (Vector2){0, 0}, 45.0f, RED);
	DrawRectanglePro((Rectangle){135, 30, gridSize - 5, 25}, (Vector2){0, 0}, 135.0f, RED);
	EndTextureMode(); // Ends drawing to render texture

	BeginTextureMode(O);	// Begin drawing to render texture O
	ClearBackground(WHITE); // Background color of the O
	// (posX, posY, radius, color)
	DrawCircle(gridSize / 2, gridSize / 2, gridSize / 2 - 5, BLUE); // Outer circle
	DrawCircle(gridSize / 2, gridSize / 2, 45, WHITE);				// Inner Circle
	EndTextureMode();												// Ends drawing to render texture

	// Buttons
	Rectangle buttons[3] = {
		(Rectangle){250, 260, 300, 100},
		(Rectangle){250, 380, 300, 100},
		(Rectangle){250, 500, 300, 100}};

	// Main gameplay loop
	while (!WindowShouldClose()) // WindowShould Close checks if ESC key is pressed
	{
		/**
		 *
		 *	@brief Checks which navigation state the game is at
		 * 	@param currentScreen 0 = Home, 1 = Difficulty, 2 = Player selection, 3 = Main game
		 * 	@param DrawText (*text, posX, posY, fontSize, color)
		 *	@if case 0 = Home

		 * 	@authors Ryan, Kang Le, Clarissa
		 *
		 */
		switch (currentScreen) // When the variable of currentScreen changes, it will change screen accordingly
		{
		case 0:													 // Home screen
			pressedButton = checkButton(buttons);				 // Check which button has been pressed and assign it to pressedButton
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
				goto EXIT; // Exit the game
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
				// rectangle(already declared initially), roundness, segments, olor
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

			break;

		case 1:
			// Difficulty
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
			break;

		case 2:
			// Player selection
			pressedButton = checkButton(buttons);

			if ((pressedButton != -1) && IsMouseButtonPressed(0))
			{
				if (pressedButton == 0)
				{
					human = 'X';
				}
				else if (pressedButton == 1)
				{
					human = 'O';
				}
				else
				{
					human = (char[2]){'X', 'O'}[random(2)];
				}
				PlaySound(gameStartSound);
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
			break;

		case 3:
			// Main game
			switch (gameState)
			{
			case 0:
				grid_index = mouseCollide(GetMousePosition(), (Vector2){155, 155}, gridSize, gridThickness);
				if ((gameMode == '0' || human == playerTurn))
				{
					if (IsMouseButtonPressed(0) && grid_index != -1 && grid[grid_index] == ' ')
					{
						PlaySound(placeTokenSound);
						grid[grid_index] = playerTurn; // Place the player token on the grid
						playerTurn = switchPlayer(playerTurn);
						emptySpaces--;
					}
				}
				else if (human != playerTurn)
				{
					if (gameMode == '1')
					{
						normalAI(grid, playerTurn, emptySpaces);
					}
					else
					{
						impossibleAI(grid, playerTurn, emptySpaces);
					}
					playerTurn = switchPlayer(playerTurn);
					emptySpaces--;
				}

				if (checkWinner('X', grid) == 1)
				{
					winChecker = 'X';
					gameState = 1;
				}
				else if (checkWinner('O', grid) == 1)
				{
					winChecker = 'O';
					gameState = 1;
				}
				else if (emptySpaces == 0)
				{
					winChecker = '0';
					gameState = 1;
				}
				break;

			case 1:
				// Delay the game for some time after a win and show counter
				if (counter >= timer)
				{
					PlaySound(gameOverSound);
					gameState = 2;
					counter = 0;
				}
				else
				{
					counter++;
				}
				break;

			case 2:
				// Reset the game
				resetGrid(grid);
				winChecker = 0;
				gameState = 0;
				playerTurn = 'X';
				emptySpaces = 9;
				break;
			}

			pressedButton = -1;
			if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){25, 15, 115, 105}))
				pressedButton = 1;

			// Drawing the game screen and main grid
			BeginDrawing();
			BeginTextureMode(screen);
			// Render Game background
			ClearBackground(WHITE);
			textureScroll -= 0.5f;
			DrawTextureEx(gamebackground, (Vector2){textureScroll, 0}, 0.0f, 2.0f, WHITE);
			DrawTextureEx(gamebackground, (Vector2){menuBackground.width * 2 + textureScroll, 0}, 0.0f, 2.0f, WHITE);

			DrawRectangle(145, 145, (gridSize * 3 + gridThickness * 2) + 20, (gridSize * 3 + gridThickness * 2) + 20, BLACK); // 150, 20
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (grid[j * 3 + i] != ' ')
					{
						DrawTextureRec((grid[j * 3 + i] == 'X') ? X.texture : O.texture, (Rectangle){0, 0, gridSize, -gridSize}, (Vector2){i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155}, WHITE);
					}
					else
					{
						if (CheckCollisionPointRec((Vector2){GetMouseX(), GetMouseY()}, (Rectangle){i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize}))
						{
							DrawRectangle(i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize, LIGHTGRAY);
						}
						else
						{
							DrawRectangle(i * (gridSize + gridThickness) + 155, j * (gridSize + gridThickness) + 155, gridSize, gridSize, WHITE);
						}
					}
				}
			}

			switch (winChecker)
			{
			case 'X':
				DrawText("Player X wins!", 145, 675, 75, BLACK);
				break;
			case 'O':
				DrawText("Player O wins!", 145, 675, 75, BLACK);
				break;
			case '0':
				DrawText("Draw", 300, 675, 75, BLACK);
				break;
			}
			EndTextureMode();
			DrawTextureRec(screen.texture, (Rectangle){0, 0, screenWidth, -screenHeight}, (Vector2){0, 0}, WHITE);
			// Home button
			DrawRectangleRounded((Rectangle){45, 45, 75, 75}, 0.2, 5, (pressedButton == 1) ? BLACK : GRAY);
			DrawTriangle((Vector2){25, 55}, (Vector2){140, 55}, (Vector2){82.5, 15}, (pressedButton == 1) ? BLACK : GRAY);
			EndDrawing();

			// Exit to the home screen if the home button is pressed
			if ((pressedButton == 1) && IsMouseButtonPressed(0))
			{
				resetGrid(grid);
				gameMode = '0';
				winChecker = 0;
				gameState = 0;
				playerTurn = 'X';
				emptySpaces = 9;
				currentScreen = 0;
			}

			break;
		}
	}

// Used to exit program directly
EXIT:
	UnloadSound(buttonClickSound); // Unload sounds
	UnloadSound(gameStartSound);
	UnloadSound(gameOverSound);
	UnloadSound(backgroundMusic);
	UnloadSound(placeTokenSound);
	CloseAudioDevice(); // Close audio device

	UnloadRenderTexture(screen);   // Unload screen texture
	UnloadTexture(menuBackground); // Unload menuBackground texture
	UnloadTexture(gamebackground); // Unload menuBackground texture
	UnloadRenderTexture(X);
	UnloadRenderTexture(O);

	CloseWindow();

	return 0;
}

/**
 * @brief Check if the mouse is hovering over a grid dquare
 *
 * @param mousePos
 * @param gridPos
 * @param gridSize
 * @param gridThickness
 * @return The grid index where the mouse is over
 */
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

/**
 * @brief Check which button the mouse is over
 * @param buttons
 *
 * @return which button is pressed 0, 1, 2 or -1 if not
 */
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
