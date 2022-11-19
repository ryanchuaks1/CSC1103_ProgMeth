#ifndef SCREENS_H
#define SCREENS_H

extern float textureScroll;
extern enum GameScreen currentScreen;
extern struct Sound buttonClickSound;

enum GameScreen
{
    MainMenuScreen,
    DifficultyScreen,
    GameplayScreen,
    MultiplayerMode,
    NormalAIMode,
    ImpossibleAIMode,
};

// Potentially move this out as tic-tac-toe as an enum already
enum GameplayMode
{
    Multiplayer,
    MediumAI,
    ImpossibleAI,
};

// Main Menu Screens //
void InitMainMenuScreen();
void UpdateMainMenuScreen();
void DrawMainMenuScreen();
void UnloadMainMenuScreen();

// Difficulty Screens //
void InitDifficultyScreen();
void UpdateDifficultyScreen();
void DrawDifficultyScreen();
void UnloadDifficultyScreen();

// Gameplay Screens //
void InitGameplayScreen(enum GameplayMode mode);
void UpdateGameplayScreen();
void DrawGameplayScreen();
void UnloadGameplayScreen();

#endif