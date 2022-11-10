#include "../include/raylib.h"
#include "../include/screens.h"
#include <stdio.h>

/** ----------------------------------------------------------------------------------------------------
 * Global Variables
 ---------------------------------------------------------------------------------------------------- */
enum GameScreen currentScreen;
float textureScroll = 0.0f;
struct Sound buttonClickSound;

/** ----------------------------------------------------------------------------------------------------
 * Local functions prototype
 ---------------------------------------------------------------------------------------------------- */
static void UpdateFrame(void);

/** ----------------------------------------------------------------------------------------------------
 * @brief Main function of the program
 * This function starts the program with window and sound
 * The control of screens both loading and unloading is also controlled here
 * 
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
int main(void)
{
    InitWindow(800, 800, "Tic-Tac-Toe"); // Opens up a blank window 800 by 800 pixels
    SetTargetFPS(60);                    // Sets the frames per second of the game

    InitAudioDevice();                                             // Initiate the audio device
    Sound backgroundMusic = LoadSound("resources/fall-music.wav"); // Loads the music from resources
    buttonClickSound = LoadSound("resources/button_click.wav");    // Load button click sound
    SetSoundVolume(backgroundMusic, 1);                            // Sets the volume of the bg music

    PlaySound(backgroundMusic);                                    // Plays the background

    currentScreen = MainMenuScreen; // Set initial screen to MainMenuScreen();
    InitMainMenuScreen();           // Initiate the main menu screen, Function is called in mainmenu_screen.c
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
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
    UnloadSound(backgroundMusic);   // Unload the background music
    CloseAudioDevice();             // Close audio device
    CloseWindow();
    return 0;
}

/** ----------------------------------------------------------------------------------------------------
 * @brief UpdateDrawFrame is continuously looping while the programm is still running (window is not close)
 * This function checks what @param cuurrentScreen is and proceeds to Update and Draw that particular screen
 * If the screen returns a different exit code, it will run the function ChangeToScreen(*SCREEN*) 
 * Since FPS of program is set to 60, this function loops about 60 times a second
 * 
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
static void UpdateFrame(void)
{
    switch (currentScreen)
    {
        case MainMenuScreen:
            UpdateMainMenuScreen(); //Loop to scroll the background and check for button hover/click
            DrawMainMenuScreen();   //Loop to draw the frame
            break;

        case DifficultyScreen:
            UpdateDifficultyScreen(); //Loop to scroll the background and check for button hover/click
            DrawDifficultyScreen();   //Loop to draw the frame
            break;

        case GameplayScreen:
            UpdateGameplayScreen(); //Loop to scroll the background and check for grid hover/click
            DrawGameplayScreen();   //Loop to draw the frame
            break;
        
        default: break;
    }
}  


