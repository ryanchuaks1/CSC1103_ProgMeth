#include "../include/helpers.h"
#include "../include/tic-tac-toe.h"
#include "../include/screens.h"

/** ----------------------------------------------------------------------------------------------------
 * @brief Naviagates to the next screen, unloading the current one and init the next one
 * @param nextScreen contains which screen is the targer screen
 *
 * @date helpers.c last updated 17/11/2022
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
void navigate(GameScreen nextScreen)
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

/** ----------------------------------------------------------------------------------------------------
 * @brief Checks for button collision with some functions from raylib too
 * This function was created to reduce code repetition
 * @param buttons[3] contains which buttons to be checked
 *
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
int checkButton(Rectangle buttons[3])
{
    Vector2 mousePos = GetMousePosition(); // Gets the current mouse position
    for (int i = 0; i < 3; i++)            // Loops through all the buttons
    {
        if (CheckCollisionPointRec(mousePos, buttons[i])) // Check is there are any mouse collisions with rectangles (in this case buttons)
            return i;                                     // Return which button in the array where mouse is hovering on
    }
    return -1; // If not hovering over anything, return -1 as default
}

/** ----------------------------------------------------------------------------------------------------
 * @brief Checks value of a and b and return the min or max of it
 * This function is called from tic-tac-toe.c
 * @param a // Number to compare
 * @param b // Number to compare
 *
 * @authors Ryan, Kang Le, Clarissa, Sean, Xavier
 ---------------------------------------------------------------------------------------------------- */
int min(int a, int b)
{
    return ((a > b) ? b : a); // return smaller number
}

int max(int a, int b)
{
    return ((a > b) ? a : b); // return bigger number
}