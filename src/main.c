#include "../include/raylib.h"
#include "../include/screens.h"
#include <stdio.h>

// Global variables (Required to modify state among all the screen)
enum GameScreen currentScreen;

// Local functions prototype
static void UpdateDrawFrame(void);
static void ChangeToScreen(enum GameScreen nextScreen);

int main(void)
{
    InitWindow(800, 800, "Tic-Tac-Toe");

    // Just let main have the audio device so it can propagate down to the screens.
    InitAudioDevice();
    Sound backgroundMusic = LoadSound("resources/fall-music.wav");

    SetSoundVolume(backgroundMusic, 0.5);
    PlaySound(backgroundMusic);

    // Set initial screen to MainMenuScreen();
    currentScreen = MainMenuScreen;
    InitMainMenuScreen();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // Check what screen it is currently on and call the respective Unload Function to destroy created data to prevent segmentation fault
    switch (currentScreen)
    {
        case 1:
            UnloadMainMenuScreen();
            break;

        case 2:
            UnloadDifficultyScreen();
            break;
        
        default:
            break;
    }

    CloseAudioDevice();
    return 0;
}

// I consider this a total piece of junk ;)
// TODO : Think of ways to make this cleaner
static void ChangeToScreen(enum GameScreen nextScreen)
{
    // Unload existing screen to prevent any possible segmentation failure
    switch (currentScreen)
    {
        case MainMenuScreen:
            UnloadMainMenuScreen();
            break;

        case DifficultyScreen:
            UnloadDifficultyScreen();
            break;

        case GameplayScreen:
            UnloadGameplayScreen();
            break;
        
        default: break;
    }

    // Load respective initialising for next respective screen
    switch (nextScreen)
    {
        case MainMenuScreen:
            printf("Attempting to switch to main menu screen \n");
            InitMainMenuScreen();
            break;

        case DifficultyScreen:
            printf("Attempting to switch to difficulty screen \n");
            InitDifficultyScreen();
            break;

        case MultiplayerMode:
            printf("Attempting to switch to gameplay screen \n");
            InitGameplayScreen(Multiplayer);
            break;

        case NormalAIMode:
            InitGameplayScreen(MediumAI);
            break;

        case ImpossibleAIMode:
            InitGameplayScreen(ImpossibleAI);
            break;

        default : break;
    }

    // Another hacky solution that we have to redo sigh...
    if (nextScreen == NormalAIMode || nextScreen == ImpossibleAIMode || nextScreen == MultiplayerMode)
    {
        currentScreen = GameplayScreen;
    }
    else
    {
        currentScreen = nextScreen;
    }
}

// Continuously looping
static void UpdateDrawFrame(void)
{
    // Update function that has nothing related to the drawings
    switch (currentScreen)
    {
        case MainMenuScreen:
            UpdateMainMenuScreen();
            DrawMainMenuScreen();
            if (FinishMainMenuScreen() == 1)
            {
                // Transition to another Screen
                ChangeToScreen(MultiplayerMode);
            }
            else if (FinishMainMenuScreen() == 2)
            {
                ChangeToScreen(DifficultyScreen);
            }
            else if (FinishMainMenuScreen() == 3)
            {
                CloseWindow();
            }
            break;

        case DifficultyScreen:
            UpdateDifficultyScreen();
            DrawDifficultyScreen();
            if (FinishDifficultyScreen() == 1)
            {
                ChangeToScreen(NormalAIMode);
            }
            else if (FinishDifficultyScreen() == 2)
            {
                ChangeToScreen(ImpossibleAIMode);
            }
            else if (FinishDifficultyScreen() == 3)
            {
                ChangeToScreen(MainMenuScreen);                
            }
            break;

        case GameplayScreen:
            UpdateGameplayScreen();
            DrawGameplayScreen();
            break;
        
        default: break;
    }
}   