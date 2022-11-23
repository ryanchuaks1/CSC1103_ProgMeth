#include "../include/raylib.h"
#include "../include/screens.h"
#include <stdio.h>

/** ----------------------------------------------------------------------------------------------------
 * Global Variables (used across all screens)
 ---------------------------------------------------------------------------------------------------- */
GameScreen currentScreen;
bool exitWindowRequested = false;
float textureScroll = 0.0f;
Sound buttonClickSound;
Sound gameStartSound;
Sound gameOverSound;
Sound placeTokenSound;

/** ----------------------------------------------------------------------------------------------------
 * Local functions prototype
 ---------------------------------------------------------------------------------------------------- */
static void UpdateFrame(void);

/** ----------------------------------------------------------------------------------------------------
 * @brief Main function of the program
 * This function starts the program with window and sound
 * The control of screens both loading and unloading is done here
 *
 * @date main.c last updated 19/11/2022
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
int main(void)
{
    InitWindow(800, 800, "Tic-Tac-Toe"); // Opens up a blank window 800 by 800 pixels
    SetTargetFPS(60);                    // Sets the frames per second of the game

    InitAudioDevice();                                             // Initiate the audio device
    Sound backgroundMusic = LoadSound("resources/fall-music.wav"); // Loads the music from resources
    buttonClickSound = LoadSound("resources/button_click.wav");    // Load button click sound
    gameStartSound = LoadSound("resources/game_start.wav");        // Load game start sound
    gameOverSound = LoadSound("resources/game_over.wav");          // Load game start sound
    placeTokenSound = LoadSound("resources/place_token.wav");      // Load game start sound
    SetSoundVolume(backgroundMusic, 0.5);                          // Sets the volume of the bg music

    PlaySound(backgroundMusic); // Plays the background

    currentScreen = MainMenuScreen; // Set initial screen to MainMenuScreen();
    InitMainMenuScreen();           // Initiate the main menu screen, Function is called in mainmenu_screen.c

    while (!WindowShouldClose() && !exitWindowRequested) // Detect window close button or ESC key
    {
        UpdateFrame(); // Generates the Screen, Function is called in main.c
    }

    // Call the respective Unload Function to destroy created data to prevent segmentation fault
    // This runs upon the while loop ending (meaning the game has exit)
    switch (currentScreen)
    {
    case 1: UnloadMainMenuScreen(); break;
    case 2: UnloadDifficultyScreen(); break;
    case 3: UnloadGameplayScreen(); break;
    default: break;
    }
    // Unload all sounds
    UnloadSound(backgroundMusic); 
    UnloadSound(buttonClickSound);
    UnloadSound(gameStartSound);  
    UnloadSound(gameOverSound);   
    UnloadSound(placeTokenSound); 
    CloseAudioDevice();            // Close audio device
    CloseWindow();
    return 0;
}

/** ----------------------------------------------------------------------------------------------------
 * @brief UpdateDrawFrame is continuously looping while the programm is still running (window is not close)
 * This function checks what @param cuurrentScreen is and proceeds to Update and Draw that particular screen
 * Since FPS of program is set to 60, this function loops about 60 times a second
 ---------------------------------------------------------------------------------------------------- */
static void UpdateFrame(void)
{
    switch (currentScreen)
    {
    case MainMenuScreen:
        UpdateMainMenuScreen(); // Loop to scroll the background and check for button hover/click
        DrawMainMenuScreen();   // Loop to draw the frame
        break;

    case DifficultyScreen:
        UpdateDifficultyScreen(); // Loop to scroll the background and check for button hover/click
        DrawDifficultyScreen();   // Loop to draw the frame
        break;

    case GameplayScreen:
        UpdateGameplayScreen(); // Loop to scroll the background and check for grid hover/click
        DrawGameplayScreen();   // Loop to draw the frame
        break;

    default:
        break;
    }
}
