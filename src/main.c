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
            InitMainMenuScreen();
            break;

        case DifficultyScreen:
            InitDifficultyScreen();
            break;

        case MultiplayerMode:
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
            // Returns exit code will will allow the program to lead to another page
            // 1 = Multiplayer Mode
            // 2 = VS AI (Will lead to another difficulty page)
            // 3 =  Exit
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
            // Check for options selected
            // 1 = Medium AI
            // 2 = Impossible AI
            if (FinishDifficultyScreen() == 1)
            {
                ChangeToScreen(NormalAIMode);
            }
            else if (FinishDifficultyScreen() == 2)
            {
                ChangeToScreen(ImpossibleAIMode);
            }
            break;

        case MultiplayerMode:
            UpdateGameplayScreen();
            DrawGameplayScreen();
            // Check for game won
        
        default: break;
    }
}   