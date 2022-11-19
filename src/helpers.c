#include "../include/helpers.h"
#include "../include/tic-tac-toe.h"
#include "../include/screens.h"

void navigate(enum GameScreen nextScreen)
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
    default:
        break;
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
    default:
        break;
    }
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

int min(int a, int b)
{
    return ((a > b) ? b : a);
}

int max(int a, int b)
{
    return ((a > b) ? a : b);
}