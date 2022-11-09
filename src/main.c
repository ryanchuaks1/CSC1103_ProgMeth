#include "../include/raylib.h"
#include "../include/screens.h"
#include <stdio.h>

/** ----------------------------------------------------------------------------------------------------
 * Global Variables
 ---------------------------------------------------------------------------------------------------- */
enum GameScreen currentScreen;
float textureScroll = 0.0f;

/** ----------------------------------------------------------------------------------------------------
 * Local functions prototype
 ---------------------------------------------------------------------------------------------------- */
static void UpdateDrawFrame(void);
static void ChangeToScreen(enum GameScreen nextScreen);

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
    SetSoundVolume(backgroundMusic, 0.5);                          // Sets the volume of the bg music
    PlaySound(backgroundMusic);                                    // Plays the background

    currentScreen = MainMenuScreen; // Set initial screen to MainMenuScreen();
    InitMainMenuScreen();           // Initiate the main menu screen, Function is called in mainmenu_screen.c
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame(); // Generates the Screen, Function is called in main.c
    }

    // Call the respective Unload Function to destroy created data to prevent segmentation fault
    // This runs upon the while loop ending (meaning the game has exit)
    switch (currentScreen)
    {
        case 1: UnloadMainMenuScreen(); break;
        case 2: UnloadDifficultyScreen(); break;
        default: break;
    }
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
static void UpdateDrawFrame(void)
{
    switch (currentScreen)
    {
        case MainMenuScreen:
            UpdateMainMenuScreen(); //Loop to scroll the background and check for button hover/click
            DrawMainMenuScreen();   //Loop to draw the frame
            switch(FinishMainMenuScreen())
            {
                case 1: ChangeToScreen(MultiplayerMode); break;
                case 2: ChangeToScreen(DifficultyScreen); break;
                case 3: CloseWindow(); break;
            };
            break;

        case DifficultyScreen:
            UpdateDifficultyScreen(); //Loop to scroll the background and check for button hover/clic
            DrawDifficultyScreen();   //Loop to draw the frame
            switch(FinishDifficultyScreen())
            {
                case 1: ChangeToScreen(NormalAIMode); break;
                case 2: ChangeToScreen(ImpossibleAIMode); break;
                case 3: ChangeToScreen(MainMenuScreen); break;
            };
            break;

        case GameplayScreen:
            UpdateGameplayScreen();
            DrawGameplayScreen();
            break;
        
        default: break;
    }
}  

/** ----------------------------------------------------------------------------------------------------
 * @brief Change Screen according to the global variable currentScreen and the @param nextScreen
 * This function changes the current screen to the target screen by first,
 * unloading the current screen and then init the next screen
 * 
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
static void ChangeToScreen(enum GameScreen nextScreen)
{
    // Unload existing screen to prevent any possible segmentation failure
    switch (currentScreen)
    {
        case MainMenuScreen: UnloadMainMenuScreen(); break;
        case DifficultyScreen: UnloadDifficultyScreen(); break;
        case GameplayScreen: UnloadGameplayScreen(); break;
        default: break;
    }

    // Load respective initialising for next screen
    switch (nextScreen)
    {
        case MainMenuScreen:
            InitMainMenuScreen(); 
            currentScreen = nextScreen; 
            break;
        case DifficultyScreen:
            InitDifficultyScreen(); 
            currentScreen = nextScreen; 
            break;
        case MultiplayerMode: 
            InitGameplayScreen(Multiplayer); 
            currentScreen = GameplayScreen; 
            break;
        case NormalAIMode: 
            InitGameplayScreen(MediumAI); 
            currentScreen = GameplayScreen; 
            break; 
        case ImpossibleAIMode: 
            InitGameplayScreen(ImpossibleAI); 
            currentScreen = GameplayScreen; 
            break;
        default : break;
    }
}

